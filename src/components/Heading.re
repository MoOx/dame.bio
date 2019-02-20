open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "title":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(32.)),
          lineHeight(32. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Heading");

let make = children => {
  ...component,
  render: _self => {
    <TextWeb style=styles##title accessibilityRole="heading">
      ...children
    </TextWeb>;
  },
};
