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
      "backgroundImageWrapper":
        style([position(Absolute), top(Pt(0.)), left(Pct(50.))]),
      "backgroundImage":
        style([
          left(Pct(-50.)),
          width(Pt(3387. *. 0.5)),
          height(Pt(394. *. 0.5)),
        ]),
    })
  );

[@react.component]
let make = (~currentLocation, ()) => {
  <View style=styles##header>
    <View style=styles##backgroundImageWrapper>
      <ImageFromUri
        resizeMode=`contain
        style=styles##backgroundImage
        uri="/images/header-background.jpg"
      />
    </View>
    <HeaderLargeTopbar currentLocation />
    <HeaderLargeLogo />
  </View>;
};
/* <HeaderLargeMenu /> */

let default = make;
