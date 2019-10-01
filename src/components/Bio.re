open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "bioText":
        style([
          fontWeight(`_300),
          color(String("#49443A")),
          maxWidth(Pt(500.)),
        ]),
    })
  );

[@react.component]
let make = (~children) => {
  <Text style=styles##bioText> children </Text>;
};
