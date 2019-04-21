open BsReactNative;

let component = ReasonReact.statelessComponent("ContainerMainContent");

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([flexShrink(1.), alignSelf(Center), flexBasis(Pt(800.))]),
    },
  );

let make = children => {
  ...component,
  render: _self =>
    /*accessibilityRole=`webAriaMain*/
    <View style=styles##container> ...children </View>,
};
