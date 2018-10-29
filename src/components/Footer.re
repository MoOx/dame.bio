open BsReactNative;

let component = ReasonReact.statelessComponent("Footer");

let make = _children => {
  ...component,
  render: _self =>
    <View>
      <Container>
        <Text> (ReasonReact.string("Footer")) </Text>
      </Container>
    </View>
};
