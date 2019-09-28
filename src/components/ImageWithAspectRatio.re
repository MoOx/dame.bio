open Belt;
open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "imageContainer": viewStyle(~display=`flex, ~overflow=`hidden, ()),
      "image":
        imageStyle(
          ~position=`absolute,
          ~top=0.->dp,
          ~bottom=0.->dp,
          ~right=0.->dp,
          ~left=0.->dp,
          ~backgroundColor="#eee",
          (),
        ),
    })
  );

[@react.component]
let make = (~uri=?, ~ratio, ~style as s=?, ()) => {
  <View style=styles##imageContainer>
    <PlaceholderWithAspectRatio ratio>
      {uri
       ->Option.map(uri =>
           <ImageFromUri
             style=Style.(arrayOption([|Some(styles##image), s|]))
             uri
           />
         )
       ->Option.getWithDefault(React.null)}
    </PlaceholderWithAspectRatio>
  </View>;
};
