open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(~flexShrink=1., ~alignSelf=`center, ~flexBasis=800.->dp, ()),
    })
  );

[@react.component]
let make = (~children, ()) => {
  /*accessibilityRole=`webAriaMain*/
  <View style=styles##container>
    children
  </View>;
};
