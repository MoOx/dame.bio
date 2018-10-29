open BsReactNative;

let component = ReasonReact.statelessComponent("Spacer");

let styles =
  StyleSheet.create(
    Style.{
      "normal": style([width(Pt(20.)), height(Pt(20.))]),
      "large": style([width(Pt(40.)), height(Pt(40.))]),
      "small": style([width(Pt(10.)), height(Pt(10.))]),
    },
  );

let make = (~large=false, ~small=false, _) => {
  ...component,
  render: _self =>
    <View
      style={large ? styles##large : small ? styles##small : styles##normal}
    />,
};
