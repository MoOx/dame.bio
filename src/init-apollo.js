import { ApolloClient, InMemoryCache, HttpLink } from "apollo-boost";
import { IntrospectionFragmentMatcher } from "apollo-cache-inmemory";

let apolloClient = null;
let isBrowser = typeof window !== "undefined";

function create(initialState) {
  return new ApolloClient({
    connectToDevTools: isBrowser,
    ssrMode: !isBrowser, // Disables forceFetch on the server (so queries are only run once)
    link: new HttpLink({
      uri: "https://dame.bio/graphql",
      credentials: "same-origin"
    }),
    cache: new InMemoryCache({
      fragmentMatcher: new IntrospectionFragmentMatcher({
        introspectionQueryResultData: require("./introspectionQueryResult.json")
          .data
      })
    }).restore(
      initialState || (isBrowser ? window.__APOLLO_STATE__ : undefined) || {}
    )
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
