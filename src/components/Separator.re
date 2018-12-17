open BsReactNative;

let component = ReasonReact.statelessComponent("Separator");

let styles = StyleSheet.create(Style.{"separator": style([])});

let make = _ => {
  ...component,
  render: _self => <View style=styles##separator />,
};
