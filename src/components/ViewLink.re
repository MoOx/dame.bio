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
    style=BsReactNative.(
      Style.(
        arrayOption([|
          Some(style([display(Flex), flexDirection(Column)])),
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
