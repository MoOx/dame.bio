open Helpers;

open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "avatar":
        style([width(Pt(40.)), height(Pt(40.)), borderRadius(100.)]),
      "avatarEmpty":
        style([
          lineHeight(62.),
          color(String("#fff")),
          textAlign(Center),
          fontWeight(`_300),
          fontSize(Float(50.)),
          fontFamily("Georgia"),
        ]),
      "avatarDefault":
        style([
          lineHeight(40.),
          color(String("#fff")),
          textAlign(Center),
          fontWeight(`_600),
          fontSize(Float(18.)),
        ]),
      "avatarImage":
        style([
          position(Absolute),
          top(Pt(0.)),
          left(Pt(0.)),
          width(Pt(40.)),
          height(Pt(40.)),
          borderRadius(100.),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Avatar");

let notSoRandomColor = s => {
  let hue =
    Belt.List.makeBy(String.length(s), i => s.[i])
    ->Belt.List.reduce(0, (hue, char) => hue + Char.code(char))
    mod 360;
  "hsl(" ++ string_of_int(hue) ++ ", 90%, 95%)";
};

let make = (~name, ~url, _) => {
  ...component,
  render: _self =>
    <View
      style=Style.(
        flatten([|
          styles##avatar,
          style([backgroundColor(String(notSoRandomColor(name)))]),
        |])
      )>
      {
        String.length(name) > 1 ?
          <Text style=styles##avatarDefault>
            {String.sub(name, 0, 1) |> String.capitalize |> text}
          </Text> :
          <Text style=styles##avatarEmpty> {{j|¨̮|j} |> text} </Text>
      }
      <Image
        style=styles##avatarImage
        resizeMode=`contain
        source={`URI(Image.(imageURISource(~uri=url, ())))}
      />
    </View>,
};
