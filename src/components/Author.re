open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container": style([flexDirection(Row), flexWrap(Wrap)]),
      "block": style([flex(1.), flexBasis(Pt(300.))]),
      "blockTitle":
        style([
          fontSize(Float(24.)),
          marginBottom(Pt(12.)),
          color(String(Consts.Colors.pink)),
        ]),
      "blockText": style([fontSize(Float(16.)), lineHeight(16. *. 1.5)]),
      "icons": style([flexDirection(Row), justifyContent(FlexEnd)]),
      "icon": style([]),
      "iconWrapper":
        style([zIndex(1), lineHeight(24.), padding(Pt(14.))]),
      "iconBackground": style([paddingTop(Pt(3.)), paddingRight(Pt(2.))]),
    })
  );

let uriBg = "/images/avatar-background.png";
let uri = "/images/avatar.jpg";

[@react.component]
let make = () => {
  <View style=styles##container>
    <AuthorAvatar />
    <Spacer />
    <View style=styles##block>
      <Text style=styles##blockTitle> Consts.nickname->React.string </Text>
      <Text style=styles##blockText>
        <Bio> Consts.bio->React.string </Bio>
      </Text>
      <Spacer />
      <SocialIcons
        wrapperStyle=styles##icons
        iconStyle=styles##icon
        iconSize=24.
        iconWrapperFunc={(~children) =>
          <ImageBackgroundFromUri
            resizeMode=`cover
            style=styles##iconBackground
            uri="/images/circle-splash-pink.png">
            <Text style=styles##iconWrapper> children </Text>
          </ImageBackgroundFromUri>
        }
      />
    </View>
  </View>;
};
