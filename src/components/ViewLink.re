[@react.component]
let make =
    (
      ~accessibilityLabel=?,
      ~href,
      ~style as styl=?,
      ~activeStyle=?,
      ~onPress=?,
      ~onMouseEnter=?,
      ~onMouseLeave=?,
      ~children,
    ) =>
  <TextLink
    ?accessibilityLabel
    href
    style=ReactNative.(
      Style.(
        arrayOption([|
          Some(style(~display=`flex, ~flexDirection=`column, ())),
          styl,
        |])
      )
    )
    ?activeStyle
    ?onPress
    ?onMouseEnter
    ?onMouseLeave>
    children
  </TextLink>;
