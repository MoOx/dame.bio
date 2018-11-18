import * as React from "react";
import { Router, Route, browserHistory } from "react-router";
import { createApp } from "@phenomic/preset-react-app/lib/client";
import { createContainer } from "@phenomic/preset-react-app/lib/es6/src/phenomicPresetReactApp.js";

import RoutePosts from "./lib/es6/src/components/RoutePosts";
import RoutePost from "./lib/es6/src/components/RoutePost";

export default createApp(() => (
  <Router history={browserHistory}>
    <Route path="/" component={RoutePosts} />
    <Route path="/:cat/*" component={RoutePost} />
  </Router>
));

if (module.hot) {
  module.hot.accept(() => renderApp(routes));
}

// it's that easy to have for initial loading ?
// will have to double check in prod (static)
require("@phenomic/plugin-renderer-react/lib/components/Link.hash.js").default(
  window.location.hash
);
