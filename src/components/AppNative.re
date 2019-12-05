open BsReactNative;

let styles =
  Style.(StyleSheet.create({"container": style([marginTop(Pt(44.))])}));

[@react.component]
let make = () => {
  <View style=styles##container />;
};

let default = make;
