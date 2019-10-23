open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "sidebar":
        style([
          flex(1.),
          flexBasis(Pt(350.)),
          alignItems(Center),
          paddingHorizontal(Pt(20.)),
          paddingVertical(Pt(10.)),
        ]),
      "block": style([padding(Pt(20.))]),
      "blockTitle":
        style([
          fontSize(Float(24.)),
          marginBottom(Pt(12.)),
          color(String("#DE6D88")),
        ]),
      "icons": style([flexDirection(Row), justifyContent(Center)]),
      "icon": style([]),
      "iconWrapper":
        style([zIndex(1), lineHeight(24.), padding(Pt(14.))]),
      "iconBackground": style([paddingTop(Pt(3.)), paddingRight(Pt(2.))]),
    })
  );

[@react.component]
let make = (~children=?, ()) => {
  <View style=styles##sidebar>
    <Spacer size=M />
    <AuthorAvatar />
    <Spacer size=M />
    <View style=styles##block>
      <Text style=styles##blockTitle> {React.string({j|Bienvenue|j})} </Text>
      <Bio> Consts.shortBio->React.string </Bio>
    </View>
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
    <Spacer size=L />
    <DonationInvite />
    <Spacer size=L />
    <MoonPhase />
    <Spacer size=L />
    {children->Belt.Option.getWithDefault(React.null)}
  </View>;
};
