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
  uri: backendUrl + "graphql",
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
      // console.log("data", data);
      return data.refreshJwtAuthToken.authToken;
    })
    .catch(() => {
      return null;
    });
};

const errorLink = onError(({ networkError, operation, forward }) => {
  // console.log("erreur!");
  if (networkError.statusCode === 403 && store.refreshToken) {
    // console.log("erreur 403");
    store.authToken = undefined;
    return new Observable(observer => {
      refreshAccessToken(store.refreshToken)
        .then(authToken => {
          if (!authToken) {
            // console.log("logout no auth");
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
          // console.log("logout no caca");
          logout();
          observer.error(err);
        });
    });
  }
});

function create(initialState) {
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
      // until website is faster to build, we don't use the local serialized
      // state to be sure to have up to date (live) data from backend
      initialState /*|| (isBrowser ? window.__APOLLO_STATE__ : undefined)*/ ||
        {},
    ),
  });
}

export default function initApollo(initialState) {
  if (!isBrowser) {
    return create(initialState);
  }

  if (!apolloClient) {
    apolloClient = create(initialState);
  }

  return apolloClient;
}
