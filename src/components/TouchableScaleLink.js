import * as React from "react";
import PropTypes from "prop-types";

import { isActive } from "@phenomic/plugin-renderer-react/lib/components/Link.js";

import TouchableScale from "./TouchableScale.js";
import { hrefify, handlePress } from "./linkUtils";

export default function TouchableScaleLink(props, context) {
  const { style, activeStyle, ...otherProps } = props;
  const href = props.to || props.href || "";
  return (
    <TouchableScale
      {...otherProps}
      accessibilityRole="link"
      href={hrefify(href)}
      onPress={handlePress(props, context.router)}
      style={[style, isActive(href, context) && activeStyle]}
    />
  );
}

TouchableScaleLink.contextTypes = {
  router: PropTypes.object.isRequired,
};
