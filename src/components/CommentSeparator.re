open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "commentSeparator":
        style(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~height=1.->dp,
          ~backgroundColor="#f4f4f4",
          ~marginHorizontal=50.->dp,
          (),
        ),
    })
  );

[@react.component]
let make = () => {
  <View style=styles##commentSeparator />;
};
