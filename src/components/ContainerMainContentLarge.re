open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(~flexGrow=2., ~flexShrink=1., ~flexBasis=800.->dp, ()),
    })
  );

[@react.component]
let make = (~children, ()) => {
  /*accessibilityRole=`webAriaMain*/
  <View style=styles##container>
    children
  </View>;
};
