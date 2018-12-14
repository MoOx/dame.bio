// @flow

import React, { Component } from "react";
import { View, Dimensions } from "react-native";

export default class ViewportObserver extends Component {
  state = {
    hasBeenVisible: false,
    isVisible: false,
    isCompletelyVisible: false
  };

  componentDidMount() {
    this.startWatching();
  }

  componentWillUnmount() {
    this.stopWatching();
  }

  startWatching = () => {
    if (this._interval) {
      return;
    }
    this._interval = setInterval(this.check, this.props.delay || 100);
  };

  stopWatching = () => {
    clearInterval(this._interval);
  };

  check = () => {
    if (!this._view) {
      return;
    }
    // react-native
    if (this._view.measure) {
      this._view.measure((x, y, width, height, pageX, pageY) => {
        const window = Dimensions.get("window");
        const isVisible =
          window.height - pageY >= 0 &&
          pageY + height >= 0 &&
          window.width - pageX >= 0 &&
          pageX + width >= 0;
        const isCompletelyVisible =
          pageY >= 0 &&
          pageY + height != 0 &&
          pageY + height <= window.height &&
          pageX + width > 0 &&
          pageX + width <= window.width;
        if (
          this.state.isVisible !== isVisible ||
          this.state.isCompletelyVisible !== isCompletelyVisible
        ) {
          this.setState({
            hasBeenVisible: this.state.hasBeenVisible || isVisible,
            isVisible,
            isCompletelyVisible
          });
        }
      });
    }
  };

  render() {
    return (
      <View collapsable={false} ref={c => (this._view = c)}>
        {this.props.children(this.state)}
      </View>
    );
  }
}
