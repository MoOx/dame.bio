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
      <ImageBackground
        style=styles##image
        resizeMode=`contain
        source={`URI(Image.(imageURISource(~uri, ())))}
        /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
        defaultSource={`URI(Image.(defaultURISource(~uri, ())))}>
        <Text style=styles##children> ...children </Text>
      </ImageBackground>
    </TextLink>,
};
