open BsReactNative;

let component = ReasonReact.statelessComponent("Author");

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([flexDirection(Row), flexWrap(Wrap), alignItems(Center)]),
      "block": style([flex(1.), flexBasis(Pt(300.))]),
      "blockTitle":
        style([
          fontSize(Float(24.)),
          marginBottom(Pt(12.)),
          color(String("#DE6D88")),
        ]),
      "blockText":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          marginBottom(Pt(12.)),
        ]),
      "icons": style([flexDirection(Row), justifyContent(FlexEnd)]),
      "icon": style([padding(Pt(4.))]),
      "iconWrapper": style([zIndex(1), lineHeight(24.), padding(Pt(6.))]),
      "iconBackground": style([paddingTop(Pt(4.)), paddingRight(Pt(4.))]),
    },
  );

let uriBg = "/images/avatar-background.png";
let uri = "/images/avatar.jpg";

let make = _ => {
  ...component,
  render: _self =>
    <View style=styles##container>
      <AuthorAvatar />
      <Spacer />
      <View style=styles##block>
        <Text style=styles##blockTitle>
          {j|Liloue|j}->ReasonReact.string
        </Text>
        <Text style=styles##blockText> <Bio /> </Text>
        <Spacer />
        <SocialIcons
          wrapperStyle=styles##icons
          iconStyle=styles##icon
          iconSize=24.
          iconWrapperFunc={(~children) =>
            <ImageBackgroundFromUri
              resizeMode=`contain
              style=styles##iconBackground
              uri="/images/pink/circle-bg-lg.png">
              <Text style=styles##iconWrapper> ...children </Text>
            </ImageBackgroundFromUri>
          }
        />
      </View>
    </View>,
};
