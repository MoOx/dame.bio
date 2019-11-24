open Belt;
open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "avatar":
        style([
          width(Pt(40.)),
          height(Pt(40.)),
          borderRadius(Consts.Radius.avatar),
        ]),
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
          color(String("#fff")),
          textAlign(Center),
          fontWeight(`_600),
          fontSize(Float(24.)),
          lineHeight(40.),
          fontFamily("IndieFlower"),
        ]),
      "avatarImage":
        style([
          position(Absolute),
          top(Pt(0.)),
          left(Pt(0.)),
          width(Pt(40.)),
          height(Pt(40.)),
          borderRadius(Consts.Radius.avatar),
        ]),
    })
  );

let notSoRandomColor = s => {
  let hue =
    List.makeBy(String.length(s), i => s.[i])
    ->List.reduce(0, (hue, char) => hue + Char.code(char))
    mod 360;
  "hsl(" ++ string_of_int(hue) ++ ", 90%, 95%)";
};

[@react.component]
let make = (~name=?, ~url=?, ()) => {
  <View
    style=Style.(
      arrayOption([|
        Some(styles##avatar),
        name->Option.map(name =>
          style([backgroundColor(String(notSoRandomColor(name)))])
        ),
      |])
    )>
    {switch (name) {
     | Some(name) when String.length(name) > 1 =>
       <Text style=styles##avatarDefault>
         {String.sub(name, 0, 1)->String.capitalize->React.string}
       </Text>
     | _ => <Text style=styles##avatarEmpty> {j|¨̮|j}->React.string </Text>
     }}
    {switch (url) {
     | Some(url) =>
       <ImageFromUri style=styles##avatarImage resizeMode=`contain uri=url />
     | None => React.null
     }}
  </View>;
};
