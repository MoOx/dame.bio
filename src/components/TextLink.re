[@bs.module "./TextLink"] [@react.component]
external make:
  (
    ~accessibilityLabel: string=?,
    ~href: string,
    ~style: ReactNative.Style.t=?,
    ~activeStyle: ReactNative.Style.t=?,
    ~onPress: ReactNative.Event.pressEvent => unit=?,
    ~onMouseEnter: unit => unit=?,
    ~onMouseLeave: unit => unit=?,
    ~children: React.element=?
  ) =>
  React.element =
  "default";
