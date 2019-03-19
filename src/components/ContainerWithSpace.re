open BsReactNative;

let component = ReasonReact.statelessComponent("ContainerWithSpace");

let styles =
  StyleSheet.create(
    Style.{
      "wrapper": style([flex(1.), width(Pct(100.)), alignItems(Center)]),
      "container":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(SpaceBetween),
          flex(1.),
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
