import * as React from "react";
import PropTypes from "prop-types";
import cx from "classnames";
import { Text } from "react-native";

import {
  handleClick,
  handleKeyDown,
  isActive,
} from "@phenomic/plugin-renderer-react/lib/components/Link.js";

const BASENAME = process.env.PHENOMIC_APP_BASENAME || "/";

function Link(props, context) {
  const {
    to,
    style,
    activeStyle,
    className,
    activeClassName,
    ...otherProps
  } = props;
  const href = to || props.href || "";

  return (
    <Text
      {...otherProps}
      accessibilityRole="link"
      href={
        href.indexOf("://") > -1
          ? href
          : href.charAt(0) === "/"
            ? BASENAME + href.slice(1)
            : href
      }
      onClick={handleClick(props, context.router)}
      onKeyDown={handleKeyDown(props, context.router)}
      // isActive(href, context)
      style={style}
    />
  );
}

Link.contextTypes = {
  router: PropTypes.object.isRequired,
};

Link.displayName = "TextLink";

export default Link;
