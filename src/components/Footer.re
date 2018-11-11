open BsReactNative;

let component = ReasonReact.statelessComponent("Footer");

let make = _children => {
  ...component,
  render: _self =>
    <View>
      <Spacer size=XL />
      <InstagramFeed />
      <Container />
      <Spacer size=XL />
    </View>,
};
