open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "commentSeparator":
        style([
          flex(1.),
          height(Pt(1.)),
          backgroundColor(String("#f4f4f4")),
          marginHorizontal(Pt(50.)),
        ]),
    })
  );

[@react.component]
let make = () => {
  <View style=styles##commentSeparator />;
};
