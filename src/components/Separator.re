open BsReactNative;

let styles = Style.(StyleSheet.create({"separator": style([])}));

[@react.component]
let make = () => {
  <View style=styles##separator />;
};
