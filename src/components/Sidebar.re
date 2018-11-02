open BsReactNative;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.{
      "sidebar":
        style([flex(1.), flexDirection(Row), flexBasis(Pt(350.))]),
      "bar": style([backgroundColor(String("#F2DBDD")), width(Pt(4.))]),
      "blocks": style([flex(1.)]),
      "avatar": style([maxWidth(Pt(400.))]),
      "avatarDeco":
        style([
          paddingTop(Pt(25.)),
          paddingLeft(Pt(35.)),
          left(Pt(-15.)),
          paddingBottom(Pt(25.)),
        ]),
      "avatarImage":
        style([
          /* opacity(Float(0.1)), */
          borderRadius(500.),
          width(Pct(100.)),
          paddingBottom(Pct(100.)),
        ]),
      "block": style([]),
      "blockTitle":
        style([
          fontSize(Float(24.)),
          marginBottom(Pt(12.)),
          color(String("#DE6D88")),
        ]),
      "blockText":
        style([
          fontWeight(`_300),
          marginBottom(Pt(12.)),
          color(String("#49443A")),
        ]),
      "icons": style([flexDirection(Row)]),
      "icon": style([padding(Pt(4.))]),
      "iconWrapper": style([zIndex(1), lineHeight(24.), padding(Pt(6.))]),
      "iconBackground": style([paddingTop(Pt(4.)), paddingRight(Pt(4.))]),
    },
  );

let make = children => {
  ...component,
  render: _self =>
    <View style=styles##sidebar>
      <View style=styles##bar />
      <Spacer size=L />
      <View style=styles##blocks>
        <View style=styles##avatar>
          <ImageBackground
            resizeMode=`contain
            style=styles##avatarDeco
            source={
                     `URI(
                       Image.(
                         imageURISource(
                           ~uri="/images/avatar-background.png",
                           (),
                         )
                       ),
                     )
                   }>
            <Image
              style=styles##avatarImage
              source={
                       `URI(
                         Image.(
                           imageURISource(~uri="/images/avatar.jpg", ())
                         ),
                       )
                     }
            />
          </ImageBackground>
        </View>
        <View style=styles##block>
          <Text style=styles##blockTitle>
            {ReasonReact.string({j|Bienvenue|j})}
          </Text>
          <Text style=styles##blockText>
            {
              ReasonReact.string(
                {j|Nulla minus aut mollitia rem voluptatem voluptas facere. Beatae aperiam qui et quia non dolorum esse. Illum quae totam cumque sint dolor nobis. Cum aut et qui aut adipisci debitis tempora. Tempore sit at sint et maxime rerum dolorem.|j},
              )
            }
          </Text>
        </View>
        <Spacer />
        <SocialIcons
          wrapperStyle=styles##icons
          iconStyle=styles##icon
          iconSize=24.
          iconWrapperFunc={
            (~children) =>
              <ImageBackground
                resizeMode=`contain
                style=styles##iconBackground
                source={
                         `URI(
                           Image.(
                             imageURISource(
                               ~uri="/images/pink/circle-bg-lg.png",
                               (),
                             )
                           ),
                         )
                       }>
                <Text style=styles##iconWrapper> ...children </Text>
              </ImageBackground>
          }
        />
        <View> ...children </View>
      </View>
    </View>,
};
