import * as React from "react";
import PropTypes from "prop-types";

import TabBar from "./TabBar.bs.js";

function TabBarWithRouter(props, context) {
  return (
    <TabBar
      currentLocation={(context.router || {}).location || { pathname: "" }}
    />
  );
}

TabBarWithRouter.contextTypes = {
  router: PropTypes.object.isRequired,
};

TabBarWithRouter.displayName = "TabBarWithRouter";

export default TabBarWithRouter;
