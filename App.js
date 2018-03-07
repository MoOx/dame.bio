import * as React from "react";
import { Router, Route, browserHistory } from "react-router";
import { createApp } from "@phenomic/preset-react-app/lib/client";
import { createContainer } from "@phenomic/preset-react-app/lib/es6/src/phenomicPresetReactApp.js";

import Home from "./lib/es6/src/components/Home";
import Post from "./lib/es6/src/components/Post";

export default createApp(() => (
  <Router history={browserHistory}>
    <Route path="/" component={Home} />
    <Route path="/:cat/*" component={Post} />
  </Router>
));

if (module.hot) {
  module.hot.accept(() => renderApp(routes));
}
