[@bs.module "../../../../src/components/TextLink"]
external reactClass: ReasonReact.reactClass = "default";

let make =
    (
      ~href: option(string)=?,
      ~style: option(BsReactNative.Style.t)=?,
      ~activeStyle: option(BsReactNative.Style.t)=?,
      ~className: option(string)=?,
      ~activeClassName: option(string)=?,
      ~onMouseEnter=?,
      ~onMouseLeave=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={
      "href": Js.Nullable.fromOption(href),
      "style": Js.Nullable.fromOption(style),
      "onMouseEnter": Js.Nullable.fromOption(onMouseEnter),
      "onMouseLeave": Js.Nullable.fromOption(onMouseLeave),
      "activeStyle": Js.Nullable.fromOption(activeStyle),
      "className": Js.Nullable.fromOption(className),
      "activeClassName": Js.Nullable.fromOption(activeClassName),
    },
    children,
  );
