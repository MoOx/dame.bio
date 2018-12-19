open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLarge");

let styles =
  StyleSheet.create(
    Style.{
      "header":
        style([
          justifyContent(Center),
          alignItems(Center),
          paddingBottom(Pt(60.)),
          backgroundColor(String("#fefefe")),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##header>
      <HeaderLargeTopbar />
      <HeaderLargeLogo />
      <HeaderLargeMenu />
    </View>,
};
