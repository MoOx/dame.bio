open BsReactNative;

let component = ReasonReact.statelessComponent("Container");

let styles =
  StyleSheet.create(
    Style.{
      "wrapper":
        style([
          flexGrow(1.),
          flexShrink(1.),
          width(Pct(100.)),
          overflow(Hidden),
          alignItems(Center),
          backgroundColor(String("#fefefe")),
        ]),
      "container":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
          flexGrow(1.),
          flexShrink(1.),
          width(Pct(100.)),
          maxWidth(Pt(1200.)),
        ]),
    },
  );

let make = (~wrapperStyle=?, ~style as s=?, children) => {
  ...component,
  render: _self =>
    <View style=Style.(styles##wrapper->mergeOptional(wrapperStyle))>
      <View style=Style.(styles##container->mergeOptional(s))>
        ...children
      </View>
    </View>,
};
