type cb = {
  .
  "hasBeenVisible": bool,
  "isVisible": bool,
  "isCompletelyVisible": bool,
};

[@bs.module "./ViewportObserver.js"] [@react.component]
external make:
  (~style: ReactNative.Style.t=?, ~children: cb => React.element) =>
  React.element =
  "default";
