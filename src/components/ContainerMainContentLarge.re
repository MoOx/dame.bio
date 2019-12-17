open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style([flexGrow(2.), flexShrink(1.), flexBasis(Pt(800.))]),
    })
  );

[@react.component]
let make = (~children, ()) => {
  /*accessibilityRole=`webAriaMain*/
  <View style=styles##container>
    children
  </View>;
};
