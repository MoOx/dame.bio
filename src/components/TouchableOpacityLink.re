[@bs.module "./TouchableOpacityLink"]
external reactClass: ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type jsProps = {
  [@bs.optional]
  href: string,
  [@bs.optional]
  style: BsReactNative.Style.t,
  [@bs.optional]
  activeStyle: BsReactNative.Style.t,
  [@bs.optional]
  onMouseEnter: unit => unit,
  [@bs.optional]
  onMouseLeave: unit => unit,
};

let make =
    (
      ~href=?,
      ~style=?,
      ~activeStyle=?,
      ~onMouseEnter=?,
      ~onMouseLeave=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      jsProps(
        ~href?,
        ~style?,
        ~activeStyle?,
        ~onMouseEnter?,
        ~onMouseLeave?,
        (),
      ),
    children,
  );
