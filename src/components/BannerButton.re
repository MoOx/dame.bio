open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
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
    })
  );

let uri = "/images/banner-button.png";
[@react.component]
let make = (~href, ~children, ()) => {
  <ViewLink href style=styles##container>
    <ImageBackgroundFromUri style=styles##image resizeMode=`contain uri>
      <Text style=styles##children> children </Text>
    </ImageBackgroundFromUri>
  </ViewLink>;
};
