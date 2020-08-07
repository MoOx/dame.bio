[@bs.module "./TouchableOpacityLink"] [@react.component]
external make:
  (
    ~href: string=?,
    ~style: ReactNative.Style.t=?,
    ~activeStyle: ReactNative.Style.t=?,
    ~onMouseEnter: unit => unit=?,
    ~onMouseLeave: unit => unit=?,
    ~children: React.element=?
  ) =>
  React.element =
  "";
