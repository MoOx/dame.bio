open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "imageContainer": style([display(Flex), overflow(Hidden)]),
      "image":
        style([
          position(Absolute),
          top(Pt(0.)),
          bottom(Pt(0.)),
          right(Pt(0.)),
          left(Pt(0.)),
          backgroundColor(String("#eee")),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("ImageWithAspectRatio");

let make = (~uri, ~ratio, ~style as s=?, _) => {
  ...component,
  render: _self =>
    <View style=styles##imageContainer>
      <PlaceholderWithAspectRatio ratio>
        <ImageFromUri
          style=Style.(arrayOption([|Some(styles##image), s|]))
          uri
        />
      </PlaceholderWithAspectRatio>
    </View>,
};
