open BsReactNative;

let component = ReasonReact.statelessComponent("ContainerMainContent");

let styles =
  StyleSheet.create(
    Style.{"container": style([alignSelf(Center), maxWidth(Pt(800.))])},
  );

let make = children => {
  ...component,
  render: _self => <View style=styles##container> ...children </View>,
};
