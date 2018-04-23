open BsReactNative;

let component = ReasonReact.statelessComponent("Header");

let styles =
  StyleSheet.create(
    Style.(
      {
        "header":
          style([
            justifyContent(Center),
            alignItems(Center),
            marginBottom(Pt(60.))
          ])
      }
    )
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##header>
      <HeaderTopbar />
      <HeaderLogo />
      <HeaderMenu />
    </View>
};
