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
          ~backgroundColor=Consts.Colors.lightGrey,
          (),
        ),
    })
  );

[@react.component]
let make = (~uris, ~ratio, ~style as s=?) => {
  let style = Style.(arrayOption([|Some(styles##image), s|]));
  <View style=styles##imageContainer>
    <PlaceholderWithAspectRatio ratio>
      <ImageFromUris style uris />
    </PlaceholderWithAspectRatio>
  </View>;
};
