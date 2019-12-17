open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "sidebar":
        style(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~flexBasis=350.->dp,
          ~alignItems=`center,
          ~paddingHorizontal=20.->dp,
          ~paddingVertical=10.->dp,
          (),
        ),
      "block": style(~padding=20.->dp, ()),
      "blockTitle":
        style(
          ~fontSize=24.,
          ~marginBottom=12.->dp,
          ~color=Consts.Colors.pink,
          (),
        ),
      "icons": style(~flexDirection=`row, ~justifyContent=`center, ()),
      "icon": style(),
      "iconWrapper": style(~zIndex=1, ~lineHeight=24., ~padding=14.->dp, ()),
      "iconBackground": style(~paddingTop=3.->dp, ~paddingRight=2.->dp, ()),
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
    <NewsletterBox />
    <Spacer size=L />
    <SidebarCategories />
    <Spacer size=L />
    {children->Belt.Option.getWithDefault(React.null)}
  </View>;
};
