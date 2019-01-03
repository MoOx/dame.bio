import * as React from "react";
import PropTypes from "prop-types";

import AppMenu from "../../lib/es6/src/components/AppMenu.bs.js";

function AppMenuWithRouter(props, context) {
  return (
    <AppMenu
      currentLocation={(context.router || {}).location || { pathname: "" }}
    />
  );
}

AppMenuWithRouter.contextTypes = {
  router: PropTypes.object.isRequired,
};

AppMenuWithRouter.displayName = "AppMenuWithRouter";

export default AppMenuWithRouter;
