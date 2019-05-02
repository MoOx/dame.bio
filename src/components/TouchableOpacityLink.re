[@bs.module "./TouchableOpacityLink"] [@react.component]
external make:
  (
    ~href: string=?,
    ~style: BsReactNative.Style.t=?,
    ~activeStyle: BsReactNative.Style.t=?,
    ~onMouseEnter: unit => unit=?,
    ~onMouseLeave: unit => unit=?,
    ~children: React.element=?
  ) =>
  React.element =
  "";
