import * as React from "react";
import PropTypes from "prop-types";
import { TouchableOpacity } from "react-native";

import { isActive } from "@phenomic/plugin-renderer-react/lib/components/Link.js";

import { hrefify, handlePress } from "./linkUtils";

export default function TouchableOpacityLink(props, context) {
  const { style, activeStyle, ...otherProps } = props;
  const href = props.to || props.href || "";
  return (
    <TouchableOpacity
      {...otherProps}
      accessibilityRole="link"
      href={hrefify(href)}
      onPress={handlePress(props, context.router)}
      style={[style, isActive(href, context) && activeStyle]}
    />
  );
}

TouchableOpacityLink.contextTypes = {
  router: PropTypes.object.isRequired,
};
