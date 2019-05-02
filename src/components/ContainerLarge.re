open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper":
        style([
          flex(1.),
          width(Pct(100.)),
          alignItems(Center),
          backgroundColor(String("#fefefe")),
        ]),
      "container":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(SpaceBetween),
          flex(1.),
          width(Pct(100.)),
          maxWidth(Pt(1200.)),
        ]),
    })
  );

[@react.component]
let make = (~wrapperStyle=?, ~style as s=?, ~children, ()) => {
  <View style=Style.(arrayOption([|Some(styles##wrapper), wrapperStyle|]))>
    <View style=Style.(arrayOption([|Some(styles##container), s|]))>
      children
    </View>
  </View>;
};
