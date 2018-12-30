// @flow

// import React from "react";
import createReactClass from "create-react-class";
import dismissKeyboard from "react-native-web/dist/modules/dismissKeyboard";
import ScrollResponder from "react-native-web/dist/modules/ScrollResponder";

/* eslint-disable react/prefer-es6-class, react/prop-types */
const BodyAsScrollView = createReactClass({
  // propTypes: {
  //   keyboardDismissMode: oneOf(["none", "interactive", "on-drag"]),
  //   onScroll: func,
  //   @todo?
  //   scrollEventThrottle: bool,
  // },

  mixins: [ScrollResponder.Mixin],

  componentWillMount() {
    // onTouchStart: this.scrollResponderHandleTouchStart,
    // onTouchMove: this.scrollResponderHandleTouchMove,
    // onTouchEnd: this.scrollResponderHandleTouchEnd,
    // onScrollBeginDrag: this.scrollResponderHandleScrollBeginDrag,
    // onScrollEndDrag: this.scrollResponderHandleScrollEndDrag,
    // onMomentumScrollBegin: this.scrollResponderHandleMomentumScrollBegin,
    // onMomentumScrollEnd: this.scrollResponderHandleMomentumScrollEnd,
    // onStartShouldSetResponder: this.scrollResponderHandleStartShouldSetResponder,
    // onStartShouldSetResponderCapture: this.scrollResponderHandleStartShouldSetResponderCapture,
    // onScrollShouldSetResponder: this.scrollResponderHandleScrollShouldSetResponder,
    document.addEventListener("scroll", this._handleScroll);
    // onResponderGrant: this.scrollResponderHandleResponderGrant,
    // onResponderTerminationRequest: this.scrollResponderHandleTerminationRequest,
    // onResponderTerminate: this.scrollResponderHandleTerminate,
    // onResponderRelease: this.scrollResponderHandleResponderRelease,
    // onResponderReject: this.scrollResponderHandleResponderReject,
  },

  componentWillUnmount() {
    document.removeEventListener("scroll", this._handleScroll);
  },

  getInitialState() {
    return this.scrollResponderMixinGetInitialState();
  },

  _handleScroll(e) {
    if (this.props.keyboardDismissMode === "on-drag") {
      dismissKeyboard();
    }
    this.scrollResponderHandleScroll(e);
  },

  render() {
    return this.props.children || null;
  },
});

export default BodyAsScrollView;
