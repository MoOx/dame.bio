open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "commentSeparator":
        style([
          flex(1.),
          height(Pt(1.)),
          backgroundColor(String("#f4f4f4")),
          marginHorizontal(Pt(50.)),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("CommentSeparator");

let make = _ => {
  ...component,
  render: _self => <View style=styles##commentSeparator />,
};
