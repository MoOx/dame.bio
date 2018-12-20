import React from "react";
import PropTypes from "prop-types";
import { TouchableWithoutFeedback, Animated } from "react-native";

export default class TouchableScale extends React.Component {
  static propTypes = {
    ...TouchableWithoutFeedback.propTypes,
    style: Animated.View.propTypes.style,
    defaultScale: PropTypes.number.isRequired,
    activeScale: PropTypes.number.isRequired,
    tension: PropTypes.number.isRequired,
    friction: PropTypes.number.isRequired,
    pressInTension: PropTypes.number,
    pressInFriction: PropTypes.number,
    pressOutTension: PropTypes.number,
    pressOutFriction: PropTypes.number,
    useNativeDriver: PropTypes.bool,
  };

  static defaultProps = {
    defaultScale: 1,
    activeScale: 0.95,
    tension: 150,
    friction: 3,
    useNativeDriver: true,
  };

  constructor(...args) {
    super(...args);
    this.scaleAnimation = new Animated.Value(this.props.defaultScale);
  }

  handlePressIn = (...args) => {
    const props = this.props;
    const tension =
      typeof props.pressInTension !== "undefined"
        ? props.pressInTension
        : props.tension;
    const friction =
      typeof props.pressInFriction !== "undefined"
        ? props.pressInFriction
        : props.friction;

    Animated.spring(this.scaleAnimation, {
      toValue: props.activeScale,
      tension,
      friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onPressIn) {
      props.onPressIn(...args);
    }
  };

  handlePressOut = (...args) => {
    const props = this.props;
    const tension =
      typeof props.pressOutTension !== "undefined"
        ? props.pressOutTension
        : props.tension;
    const friction =
      typeof props.pressOutFriction !== "undefined"
        ? props.pressOutFriction
        : props.friction;

    Animated.spring(this.scaleAnimation, {
      toValue: props.defaultScale,
      tension,
      friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onPressOut) {
      props.onPressOut(...args);
    }
  };

  render() {
    return (
      <TouchableWithoutFeedback
        // todo: pass only TouchableWithoutFeedback's props.
        {...this.props}
        onPressIn={this.handlePressIn}
        onPressOut={this.handlePressOut}
      >
        <Animated.View
          style={[
            this.props.style,
            {
              transform: [{ scale: this.scaleAnimation }],
            },
          ]}
        >
          {this.props.children}
        </Animated.View>
      </TouchableWithoutFeedback>
    );
  }
}
