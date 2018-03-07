open BsReactNative;

let component = ReasonReact.statelessComponent("Footer");

let make = _children => {
  ...component,
  render: _self =>
    <View>
      <Container>
        <Text> (ReasonReact.stringToElement("Footer")) </Text>
      </Container>
    </View>
};
