import React from "react";
import initApollo from "./init-apollo";
import { Helmet } from "react-helmet";
import { ApolloProvider, getDataFromTree } from "react-apollo";

let isBrowser = typeof window !== "undefined";

export default ComposedComponent => {
  return class Apollo extends React.Component {
    static displayName = "withApolloClient(?)";
    static async getInitialProps(initialPropsArgs) {
      let appProps = {};
      if (ComposedComponent.getInitialProps) {
        appProps = await ComposedComponent.getInitialProps(initialPropsArgs);
      }

      // Run all GraphQL queries in the component tree
      // and extract the resulting data
      const apollo = initApollo();
      if (!isBrowser) {
        try {
          // Run all GraphQL queries
          await getDataFromTree(
            <ComposedComponent {...appProps} apolloClient={apollo} />
          );
        } catch (error) {
          // Prevent Apollo Client GraphQL errors from crashing SSR.
          // Handle them in components via the data.error prop:
          // https://www.apollographql.com/docs/react/api/react-apollo.html#graphql-query-data-error
          console.error("Error while running `getDataFromTree`", error);
        }

        // getDataFromTree does not call componentWillUnmount
        // head side effect therefore need to be cleared manually
        Head.rewind();
      }

      // Extract query data from the Apollo store
      const apolloState = apollo.cache.extract();

      return {
        ...appProps,
        apolloState
      };
    }

    constructor(props) {
      super(props);
      this.apolloClient = initApollo(props.apolloState);
    }

    render() {
      return (
        <ApolloProvider client={this.apolloClient}>
          <ComposedComponent {...this.props} />
        </ApolloProvider>
      );
    }
  };
};
