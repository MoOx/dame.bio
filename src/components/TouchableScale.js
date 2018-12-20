import React from "react";
import PropTypes from "prop-types";
import { Platform, TouchableWithoutFeedback, Animated } from "react-native";

export default class TouchableScale extends React.Component {
  static propTypes = {
    ...TouchableWithoutFeedback.propTypes,
    style: Animated.View.propTypes.style,
    defaultScale: PropTypes.number.isRequired,
    activeScale: PropTypes.number.isRequired,
    hoverScale: PropTypes.number,
    focusScale: PropTypes.number,
    tension: PropTypes.number.isRequired,
    friction: PropTypes.number.isRequired,
    pressInTension: PropTypes.number,
    pressInFriction: PropTypes.number,
    pressOutTension: PropTypes.number,
    pressOutFriction: PropTypes.number,
    mouseEnterTension: PropTypes.number,
    mouseEnterFriction: PropTypes.number,
    mouseLeaveTension: PropTypes.number,
    mouseLeaveFriction: PropTypes.number,
    hoverTension: PropTypes.number,
    hoverFriction: PropTypes.number,
    focusTension: PropTypes.number,
    focusFriction: PropTypes.number,
    useNativeDriver: PropTypes.bool,
  };

  static defaultProps = {
    defaultScale: 1,
    activeScale: 0.95,
    tension: 150,
    friction: 3,
    useNativeDriver: Platform.OS !== "web",
  };

  constructor(...args) {
    super(...args);
    this._scaleAnimation = new Animated.Value(this.props.defaultScale);
  }

  handlePressIn = (...args) => {
    const props = this.props;
    Animated.spring(this._scaleAnimation, {
      toValue: props.activeScale,
      tension: props.pressInTension || props.tension,
      friction: props.pressInFriction || props.friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onPressIn) {
      props.onPressIn(...args);
    }
  };

  handlePressOut = (...args) => {
    const props = this.props;
    Animated.spring(this._scaleAnimation, {
      toValue: props.defaultScale,
      tension: props.pressOutTension || props.tension,
      friction: props.pressOutFriction || props.friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onPressOut) {
      props.onPressOut(...args);
    }
  };

  handleMouseEnter = (...args) => {
    const props = this.props;
    if (props.hoverScale) {
      Animated.spring(this._scaleAnimation, {
        toValue: props.hoverScale,
        tension: props.mouseEnterTension || props.tension,
        friction: props.mouseEnterFriction || props.friction,
        useNativeDriver: props.useNativeDriver,
      }).start();
    }

    if (props.onMouseEnter) {
      props.onMouseEnter(...args);
    }
  };

  handleMouseLeave = (...args) => {
    const props = this.props;
    Animated.spring(this._scaleAnimation, {
      toValue: props.defaultScale,
      tension: props.mouseLeaveTension || props.tension,
      friction: props.mouseLeaveFriction || props.friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onMouseLeave) {
      props.onMouseLeave(...args);
    }
  };

  handleFocus = (...args) => {
    const props = this.props;
    if (props.focusScale) {
      Animated.spring(this._scaleAnimation, {
        toValue: props.focusScale,
        tension: props.focusTension || props.tension,
        friction: props.focusFriction || props.friction,
        useNativeDriver: props.useNativeDriver,
      }).start();
    }

    if (props.onFocus) {
      props.onFocus(...args);
    }
  };

  handleBlur = (...args) => {
    const props = this.props;
    Animated.spring(this._scaleAnimation, {
      toValue: props.defaultScale,
      tension: props.blurTension || props.tension,
      friction: props.blurFriction || props.friction,
      useNativeDriver: props.useNativeDriver,
    }).start();

    if (props.onBlur) {
      props.onBlur(...args);
    }
  };

  render() {
    return (
      <TouchableWithoutFeedback
        // todo: pass only TouchableWithoutFeedback's props.
        {...this.props}
        onPressIn={this.handlePressIn}
        onPressOut={this.handlePressOut}
        onMouseEnter={this.handleMouseEnter}
        onMouseLeave={this.handleMouseLeave}
        onFocus={this.handleFocus}
        onBlur={this.handleBlur}
      >
        <Animated.View
          style={[
            this.props.style,
            {
              transform: [{ scale: this._scaleAnimation }],
            },
          ]}
        >
          {this.props.children}
        </Animated.View>
      </TouchableWithoutFeedback>
    );
  }
}
