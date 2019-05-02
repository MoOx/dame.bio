open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "header":
        style([
          justifyContent(Center),
          alignItems(Center),
          backgroundColor(String("#fefefe")),
        ]),
    })
  );

[@react.component]
let make = (~currentLocation, ()) => {
  <View style=styles##header>
    <HeaderLargeTopbar currentLocation />
    <HeaderLargeLogo />
  </View>;
};
/* <HeaderLargeMenu /> */

let default = make;
