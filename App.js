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

RoutePosts.getAllPossibleUrls = async ({ path }) => {
  if (path == "/") {
    return ["/"];
  }
  if (path == "/after/:after") {
    return apolloClient
      .query({
        query: gql`
          {
            posts(first: 1000, where: { status: PUBLISH }) {
              edges {
                cursor
              }
            }
          }
        `
      })
      .then(({ data }) => {
        // console.log(`received data ${JSON.stringify(data, null, 2)}`);
        return data.posts.edges
          .map(item => {
            try {
              return "/after/" + item.cursor + "/";
            } catch (e) {
              console.log(`received error ${e}`);
              console.log(JSON.stringify(item, null, 2));
            }
          })
          .filter(i => i);
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
    <Route path="/after/:after" component={RoutePosts} />
    <Route path="/:cat/*" component={RoutePost} />
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
