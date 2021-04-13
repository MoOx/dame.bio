open Belt
open ReactNative

let styles = {
  open Style
  StyleSheet.create({"container": style(~overflow=#hidden, ())})
}

@react.component
let make = (~ratio, ~style as s=?, ~children=?, ()) =>
  <View
    pointerEvents=#boxNone
    style={
      open Style
      arrayOption([Some(style(~width=100.->pct, ~paddingBottom=(100. *. ratio)->pct, ())), s])
    }>
    {children
    ->Option.map(c =>
      <View style={Style.arrayOption([Some(StyleSheet.absoluteFill), s])}> c </View>
    )
    ->Option.getWithDefault(React.null)}
  </View>
