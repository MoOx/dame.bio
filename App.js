import * as React from "react";
import { Router, Route, browserHistory } from "react-router";
import { AppRegistry } from "react-native-web";
import { createApp } from "@phenomic/preset-react-app/lib/client";
import { createContainer } from "@phenomic/preset-react-app/lib/es6/src/phenomicPresetReactApp.bs.js";

import gql from "graphql-tag";
import initApollo from "./src/init-apollo.js";
import RoutePosts from "./lib/es6/src/components/RoutePosts.bs.js";
import RoutePost from "./lib/es6/src/components/RoutePost.bs.js";

let apolloClient = initApollo();

let first = 1000;

RoutePosts.getAllPossibleUrls = async ({ path }) => {
  if (path == "/") {
    return ["/"];
  }
  if (path.includes("/after/:after")) {
    return apolloClient
      .query({
        query: gql`
          {
            posts(first: ${first}, where: { status: PUBLISH }) {
              edges {
                cursor
                node {
                  categories {
                    nodes {
                      slug
                    }
                  }
                }
              }
            }
          }
        `
      })
      .then(({ data }) => {
        // console.log(`received data ${JSON.stringify(data, null, 2)}`);
        return data.posts.edges.reduce((acc, item) => {
          try {
            acc.push("/after/" + item.cursor + "/");
            if (
              item.node &&
              item.node.categories &&
              item.node.categories.nodes
            ) {
              item.node.categories.nodes.forEach(c => {
                acc.push("/" + c.slug + "/");
                acc.push("/" + c.slug + "/after/" + item.cursor + "/");
              });
            }
          } catch (e) {
            console.log(`received error ${e}`);
            console.log(JSON.stringify(item, null, 2));
          }
          return acc;
        }, []);
      })
      .catch(error => {
        console.log(`received error ${error}`);
        return [];
      });
  }
  return [];
};

RoutePost.getAllPossibleUrls = () => {
  return [];
};

const routes = () => (
  <Router history={browserHistory}>
    <Route path="/" component={RoutePosts} />
    <Route path="/after/:cursorAfter" component={RoutePosts} />
    <Route path="/:categorySlug/" component={RoutePosts} />
    <Route path="/:categorySlug/after/:cursorAfter" component={RoutePosts} />
    <Route path="/:categorySlug/*" component={RoutePost} />
  </Router>
);

const render = (rootComponent, rootTag) => {
  AppRegistry.registerComponent("App", () => () => rootComponent);
  AppRegistry.runApplication("App", { rootTag });
};

export default createApp(routes, render);

if (module.hot) {
  module.hot.accept(() => renderApp(routes, render));
}

// it's that easy to have for initial loading ?
// will have to double check in prod (static)
if (typeof window !== "undefined") {
  require("@phenomic/plugin-renderer-react/lib/components/Link.hash.js").default(
    window.location.hash
  );
}
