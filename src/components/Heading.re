open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "title":
        style([
          fontSize(Float(40.)),
          lineHeight(40. *. 1.2),
          color(String("#005465")),
          fontWeight(`_300),
        ]),
    })
  );

[@react.component]
let make = (~children, ()) => {
  <Text style=styles##title /*accessibilityRole=`header*/> children </Text>;
};
