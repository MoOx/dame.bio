import { ApolloClient, InMemoryCache, HttpLink } from "apollo-boost";
// import fetch from 'isomorphic-fetch'

let apolloClient = null;
let isBrowser = typeof window !== "undefined";

// // Polyfill fetch() on the server (used by apollo-client)
// if (!isBrowser) {
//   global.fetch = fetch
// }

function create(initialState) {
  return new ApolloClient({
    connectToDevTools: isBrowser,
    ssrMode: !isBrowser, // Disables forceFetch on the server (so queries are only run once)
    link: new HttpLink({
      uri: "https://dame.bio/graphql",
      credentials: "same-origin"
    }),
    cache: new InMemoryCache().restore(initialState || {})
  });
}

export default function initApollo(initialState) {
  if (!apolloClient) {
    apolloClient = create(initialState);
  }

  return apolloClient;
}
