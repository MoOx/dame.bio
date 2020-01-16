import {
  ApolloClient,
  InMemoryCache,
  HttpLink,
  ApolloLink,
  gql,
} from "apollo-boost";
/* eslint-disable */
import { Observable } from "apollo-link";
import { onError } from "apollo-link-error";
import { IntrospectionFragmentMatcher } from "apollo-cache-inmemory";
/* eslint-enable */

import { backendUrl } from "./Consts.bs";
import { store, saveStore } from "./Storage.bs";
import { logout } from "./Auth.bs";

let apolloClient = null;
const isBrowser = typeof window !== "undefined";

const httpLink = new HttpLink({
  uri: backendUrl + "/graphql",
  credentials: "same-origin",
});
const middlewareLink = new ApolloLink((operation, forward) => {
  try {
    if (store.authToken !== undefined) {
      operation.setContext({
        headers: {
          authorization: "Bearer " + store.authToken,
        },
      });
    }
  } catch (e) {
    // eslint stfu
    console.error(e);
  }

  return forward(operation);
});

const MUTATION_REFRESH_ACCESS_TOKEN = gql`
  mutation refreshAccessToken(
    $RefreshJwtAuthTokenInput: String!
    $clientMutationId: String!
  ) {
    refreshJwtAuthToken(
      input: {
        jwtRefreshToken: $RefreshJwtAuthTokenInput
        clientMutationId: $clientMutationId
      }
    ) {
      authToken
    }
  }
`;
export const refreshAccessToken = RefreshJwtAuthTokenInput => {
  return apolloClient
    .mutate({
      mutation: MUTATION_REFRESH_ACCESS_TOKEN,
      variables: {
        RefreshJwtAuthTokenInput,
        clientMutationId: "refreshAccessToken",
      },
    })
    .then(({ data }) => {
      return data.refreshJwtAuthToken.authToken;
    })
    .catch(() => {
      return null;
    });
};

const errorLink = onError(arg => {
  const { graphQLErrors, networkError, operation, forward } = arg;
  if (graphQLErrors) {
    console.log("graphQLErrors", graphQLErrors);
  }
  if (networkError && networkError.statusCode === 403 && store.refreshToken) {
    store.authToken = undefined;
    return new Observable(observer => {
      refreshAccessToken(store.refreshToken)
        .then(authToken => {
          if (!authToken) {
            logout();
          } else {
            store.authToken = authToken;
            saveStore();
            operation.setContext(({ headers }) => {
              return {
                headers: {
                  ...headers,
                  authorization: "Bearer " + store.authToken,
                },
              };
            });
          }
          const subscriber = {
            next: observer.next.bind(observer),
            error: observer.error.bind(observer),
            complete: observer.complete.bind(observer),
          };
          // Retry last failed request
          forward(operation).subscribe(subscriber);
        })
        .catch(err => {
          logout();
          observer.error(err);
        });
    });
  }
});

function create(initialState, initialOptions = {}) {
  return new ApolloClient({
    connectToDevTools: isBrowser,
    ssrMode: !isBrowser, // Disables forceFetch on the server (so queries are only run once)
    link: middlewareLink.concat(errorLink).concat(httpLink),
    cache: new InMemoryCache({
      fragmentMatcher: new IntrospectionFragmentMatcher({
        introspectionQueryResultData: require("./introspectionQueryResult.json")
          .data,
      }),
    }).restore(
      initialState ||
        (isBrowser && initialOptions.canRestoreInitialState
          ? window.__APOLLO_STATE__
          : undefined) ||
        {},
    ),
  });
}

export default function initApollo(initialState, initialOptions) {
  if (!isBrowser) {
    return create(initialState, initialOptions);
  }

  if (!apolloClient) {
    apolloClient = create(initialState, initialOptions);
  }

  return apolloClient;
}
