open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "title":
        style([
          fontSize(Float(40.)),
          lineHeight(40. *. 1.2),
          color(String("#005465")),
          fontWeight(`_300),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Heading");

let make = children => {
  ...component,
  render: _self => {
    <Text style=styles##title /*accessibilityRole=`header*/>
      ...children
    </Text>;
  },
};
