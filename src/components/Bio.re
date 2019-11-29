open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "bioText":
        style(
          ~fontWeight=`_300,
          ~fontSize=14.,
          ~lineHeight=14. *. 1.5,
          ~color=Consts.Colors.darkLabel,
          ~maxWidth=500.->dp,
          (),
        ),
    })
  );

[@react.component]
let make = (~children) => {
  <Text style=styles##bioText> children </Text>;
};
