open BsReactNative;

let imageRatio = 240. /. 350.;

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

let make = (~uri, ~style=?, _) => {
  ...component,
  render: _self =>
    <View style=styles##imageContainer>
      <View
        style={Style.style([
          Style.width(Pct(100.)),
          Style.paddingBottom(Pct(100. *. imageRatio)),
        ])}>
        <ImageFromUri
          style={Style.concat([
            styles##image,
            style->Belt.Option.getWithDefault(Style.style([])),
          ])}
          uri
        />
      </View>
    </View>,
};
