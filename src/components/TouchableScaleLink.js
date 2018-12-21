import * as React from "react";
import PropTypes from "prop-types";
import cx from "classnames";
import { Linking } from "react-native";
import {
  handleClick,
  handleKeyDown,
  handleEvent,
  isActive,
} from "@phenomic/plugin-renderer-react/lib/components/Link.js";

import { origin, handlePress } from "./TouchableOpacityLink.js";
import TouchableScale from "./TouchableScale.js";

const BASENAME = process.env.PHENOMIC_APP_BASENAME || "/";

function Link(props, context) {
  const { to, style, activeStyle, ...otherProps } = props;
  const href = to || props.href || "";

  return (
    <TouchableScale
      {...otherProps}
      accessibilityRole="link"
      href={
        href.indexOf("://") > -1
          ? href
          : href.charAt(0) === "/"
            ? BASENAME + href.slice(1)
            : href
      }
      onPress={handlePress(props, context.router)}
      style={[style, isActive(href, context) && activeStyle]}
    />
  );
}

Link.contextTypes = {
  router: PropTypes.object.isRequired,
};

Link.displayName = "TouchableScaleLink";

export default Link;
