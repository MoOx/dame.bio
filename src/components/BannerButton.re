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

let make = (~onPress, children) => {
  ...component,
  render: _self =>
    <TouchableOpacity onPress style=styles##container>
      <ImageBackground
        style=styles##image
        resizeMode=`contain
        source={
                 `URI(
                   Image.(
                     imageURISource(
                       ~uri="/images/banner-button.png",
                       /* ~width=748. /. 2.,
                          ~height=115. /. 2., */
                       (),
                     )
                   ),
                 )
               }>
        <Text style=styles##children> ...children </Text>
      </ImageBackground>
    </TouchableOpacity>,
};
