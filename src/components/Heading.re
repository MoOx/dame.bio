open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "title":
        style(
          ~fontSize=40.,
          ~lineHeight=40. *. 1.2,
          ~color="#005465",
          ~fontWeight=`_300,
          (),
        ),
    })
  );

[@react.component]
let make = (~children, ()) => {
  <Text style=styles##title /*accessibilityRole=`header*/> children </Text>;
};
