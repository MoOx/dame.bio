open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([
          justifyContent(Center),
        ])
    },
  );

let component = ReasonReact.statelessComponent("LoadingIndicator");

let make = _children => {
  ...component,
  render: _self =>
    <View>
      <Spacer size=XXL />
      <ActivityIndicator size=`large />
      <Spacer size=XXL />
    </View>,
};
