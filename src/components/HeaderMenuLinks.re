open ReactNative;

let textColor = Consts.Colors.light;

let styles =
  Style.(
    StyleSheet.create({
      "container": viewStyle(~flexDirection=`row, ()),
      "link":
        textStyle(
          ~padding=10.->dp,
          ~fontSize=14.,
          ~fontWeight=`_500,
          ~lineHeight=14. *. 2.,
          ~color=textColor,
          (),
        ),
      "linkActive":
        textStyle(
          ~textDecorationLine=`underline,
          ~textDecorationStyle=`solid,
          (),
        ),
    })
  );

let renderItem = (~index as _, ~url, ~label, ~isActive) => {
  <TextLink
    key=url
    href=url
    style=Style.(
      arrayOption([|
        Some(styles##link),
        isActive ? Some(styles##linkActive) : None,
      |])
    )>
    label->React.string
  </TextLink>;
};

[@react.component]
let make = (~currentLocation) => {
  <View style=styles##container>
    <WpMenu id="TWVudTo5NTk=" currentLocation renderItem />
  </View>;
};
