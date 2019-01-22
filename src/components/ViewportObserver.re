[@bs.module "./ViewportObserver"]
external viewportObserver: ReasonReact.reactClass = "default";

type cb = {
  .
  "hasBeenVisible": bool,
  "isVisible": bool,
  "isCompletelyVisible": bool,
};

let make = (children: cb => ReasonReact.reactElement) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=viewportObserver,
    ~props=Js.Obj.empty(),
    children,
  );
