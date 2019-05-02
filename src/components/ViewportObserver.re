type cb = {
  .
  "hasBeenVisible": bool,
  "isVisible": bool,
  "isCompletelyVisible": bool,
};

[@bs.module "./ViewportObserver.js"] [@react.component]
external make: (~children: cb => React.element) => React.element = "default";
