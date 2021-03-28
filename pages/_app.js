// @flow

import * as React from "react";
// import App from "next/app";
import { init } from "@socialgouv/matomo-next";
import { ApolloProvider } from "@apollo/client";
import { useApollo } from "../src/apolloClient";

const App = ({ Component, pageProps }) => {
  React.useEffect(() => {
    init({
      url: "https://a.moox.fr",
      jsTrackerFile: "m.js",
      phpTrackerFile: "m",
      siteId: 2,
    });
  }, []);

  const apolloClient = useApollo(pageProps);
  return (
    <ApolloProvider client={apolloClient}>
      <Component {...pageProps} />
    </ApolloProvider>
  );
};

export default App;
