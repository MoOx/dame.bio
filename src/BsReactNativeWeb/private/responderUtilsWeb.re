let responderHandlers =
    (
      ~onMoveShouldSetResponder=?,
      ~onMoveShouldSetResponderCapture=?,
      ~onResponderGrant=?,
      ~onResponderMove=?,
      ~onResponderReject=?,
      ~onResponderRelease=?,
      ~onResponderTerminate=?,
      ~onResponderTerminationRequest=?,
      ~onStartShouldSetResponder=?,
      ~onStartShouldSetResponderCapture=?,
      (),
    )
    : BsReactNative.Types.touchResponderHandlers => {
  onMoveShouldSetResponder,
  onMoveShouldSetResponderCapture,
  onResponderGrant,
  onResponderMove,
  onResponderReject,
  onResponderRelease,
  onResponderTerminate,
  onResponderTerminationRequest,
  onStartShouldSetResponder,
  onStartShouldSetResponderCapture,
};
