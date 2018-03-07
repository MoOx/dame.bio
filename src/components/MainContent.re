open BsReactNative;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.({"container": style([flex(2.), flexBasis(Pt(800.))])})
  );

let make = children => {
  ...component,
  render: _self => <View style=styles##container> ...children </View>
};
