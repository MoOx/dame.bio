open ReactNative;

let component = ReasonReact.statelessComponent("Footer");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <View> <Text> (ReasonReact.stringToElement("Footer")) </Text> </View>
};
