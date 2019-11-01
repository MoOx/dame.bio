open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "header":
        style(
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#fefefe",
          ~overflow=`hidden,
          (),
        ),
      "backgroundImageWrapper":
        style(~position=`absolute, ~top=0.->dp, ~left=50.->pct, ()),
      "backgroundImage":
        style(
          ~left=(-50.)->pct,
          ~width=(3387. *. 0.5)->dp,
          ~height=(394. *. 0.5)->dp,
          (),
        ),
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
