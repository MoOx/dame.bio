open ReactNative;

let styles =
  Style.(StyleSheet.create({"container": style(~marginTop=44.->dp, ())}));

[@react.component]
let make = () => {
  <View style=styles##container />;
};

let default = make;
