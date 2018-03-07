open BsReactNative;

let component = ReasonReact.statelessComponent("AppNative");

let styles =
  StyleSheet.create(Style.({"container": style([marginTop(Pt(44.))])}));

let make = _children => {
  ...component,
  render: _self => <View style=styles##container> <Header /> </View>
};

let default = ReasonReact.wrapReasonForJs(~component, (_) => make([||]));
