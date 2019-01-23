open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLarge");

let styles =
  StyleSheet.create(
    Style.{
      "header":
        style([
          justifyContent(Center),
          alignItems(Center),
          backgroundColor(String("#fefefe")),
        ]),
    },
  );

let make = (~currentLocation, _children) => {
  ...component,
  render: _self =>
    <View style=styles##header>
      <HeaderLargeTopbar currentLocation />
      <HeaderLargeLogo />
    </View>,
  /* <HeaderLargeMenu /> */
};

[@bs.deriving abstract]
type jsProps = {currentLocation: {. "pathname": string}};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~currentLocation=jsProps->currentLocationGet, [||])
  );
