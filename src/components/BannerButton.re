open BsReactNative;

let component = ReasonReact.statelessComponent("BannerButton");

let styles =
  StyleSheet.create(
    Style.{
      "container": style([display(Flex)]),
      "image": style([flexGrow(1.)]),
      "children":
        style([
          zIndex(1),
          fontFamily("IndieFlower"),
          fontWeight(`Bold),
          fontSize(Float(24.)),
          paddingHorizontal(Pt(60.)),
          paddingVertical(Pt(20.)),
          color(String("#fff")),
        ]),
    },
  );

let uri = "/images/banner-button.png";
let make = (~href, children) => {
  ...component,
  render: _self =>
    <TextLink href style=styles##container>
      <ImageBackgroundFromUri style=styles##image resizeMode=`contain uri>
        <Text style=styles##children> ...children </Text>
      </ImageBackgroundFromUri>
    </TextLink>,
};
