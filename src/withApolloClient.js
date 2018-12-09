import React from "react";
import initApollo from "./init-apollo";
import { Helmet } from "react-helmet";
import { ApolloProvider, getDataFromTree } from "react-apollo";

let isBrowser = typeof window !== "undefined";

export default (ComposedComponent, getAllPossibleUrls) => {
  return class Apollo extends React.Component {
    static displayName = "withApolloClient(?)";
    static async getInitialProps(initialPropsArgs) {
      let appProps = initialPropsArgs;
      if (ComposedComponent.getInitialProps) {
        appProps = await ComposedComponent.getInitialProps(initialPropsArgs);
      }

      // Run all GraphQL queries in the component tree
      // and extract the resulting data
      const apollo = initApollo();
      if (!isBrowser) {
        console.log(
          "SSR/Apollo: retrieving data for " + initialPropsArgs.pathname + "..."
        );
        try {
          // Run all GraphQL queries
          await getDataFromTree(
            <ApolloProvider client={apollo}>
              <ComposedComponent status="ready" {...appProps} />
            </ApolloProvider>
          );
        } catch (error) {
          // Prevent Apollo Client GraphQL errors from crashing SSR.
          // Handle them in components via the data.error prop:
          // https://www.apollographql.com/docs/react/api/react-apollo.html#graphql-query-data-error
          console.error("Error while running `getDataFromTree`", error);
        }

        // getDataFromTree does not call componentWillUnmount
        // head side effect therefore need to be cleared manually
        Helmet.rewind();
      }

      // Extract query data from the Apollo store
      const apolloState = apollo.cache.extract();
      return {
        ...appProps,
        apolloState
      };
    }

    static async getAllPossibleUrls(...args) {
      if (ComposedComponent.getAllPossibleUrls) {
        return await ComposedComponent.getAllPossibleUrls(...args);
      }
      if (getAllPossibleUrls) {
        return await getAllPossibleUrls(...args);
      }
      console.warn(
        "No getAllPossibleUrls() defined from " + ComposedComponent.displayName
      );
      return [];
    }

    constructor(props) {
      super(props);
      this.apolloClient = initApollo(props.apolloState);
    }

    render() {
      return (
        <ApolloProvider client={this.apolloClient}>
          <ComposedComponent {...this.props} />
          {!isBrowser &&
            this.props.apolloState && (
              <script
                dangerouslySetInnerHTML={{
                  __html: `window.__APOLLO_STATE__=${JSON.stringify(
                    this.props.apolloState
                  ).replace(/</g, "\\u003c")};`
                }}
              />
            )}
        </ApolloProvider>
      );
    }
  };
};
