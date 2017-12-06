open ReactNative;

let component = ReasonReact.statelessComponent("Header");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <View> <Text> (ReasonReact.stringToElement("Header!")) </Text> </View>
};
