import * as React from "react";
import PropTypes from "prop-types";

import Header from "./Header.bs.js";

function HeaderWithRouter(props, context) {
  return (
    <Header
      currentLocation={(context.router || {}).location || { pathname: "" }}
    />
  );
}

HeaderWithRouter.contextTypes = {
  router: PropTypes.object.isRequired,
};

HeaderWithRouter.displayName = "HeaderWithRouter";

export default HeaderWithRouter;
