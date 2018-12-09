open BsReactNative;
open Helpers;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.{
      "container": style([flexDirection(Row), alignItems(Center)]),
      "avatar": style([flexBasis(Pt(256.))]),
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
      "block": style([flex(1.)]),
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
          fontWeight(`_300),
          marginBottom(Pt(12.)),
          color(String("#49443A")),
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
      <View style=styles##avatar>
        <ImageBackground
          resizeMode=`contain
          style=styles##avatarDeco
          source={`URI(Image.(imageURISource(~uri=uriBg, ())))}
          /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
          defaultSource={`URI(Image.(defaultURISource(~uri=uriBg, ())))}>
          <Image
            style=styles##avatarImage
            source={`URI(Image.(imageURISource(~uri, ())))}
            /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
            defaultSource={`URI(Image.(defaultURISource(~uri, ())))}
          />
        </ImageBackground>
      </View>
      <Spacer />
      <View style=styles##block>
        <Text style=styles##blockTitle> {{j|Liloue|j} |> text} </Text>
        <Text style=styles##blockText>
          {
            {j|Curieuse et gourmande, je vis dans la région toulousaine à la campagne. Passionnée de cuisine et de potager bio, je crée des recettes sans gluten, souvent sans lactose et parfois sans oeufs.|j}
            |> text
          }
        </Text>
        <Spacer />
        <SocialIcons
          wrapperStyle=styles##icons
          iconStyle=styles##icon
          iconSize=24.
          iconWrapperFunc={
            (~children) => {
              let uri = "/images/pink/circle-bg-lg.png";
              <ImageBackground
                resizeMode=`contain
                style=styles##iconBackground
                source={`URI(Image.(imageURISource(~uri, ())))}
                /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
                defaultSource={`URI(Image.(defaultURISource(~uri, ())))}>
                <Text style=styles##iconWrapper> ...children </Text>
              </ImageBackground>;
            }
          }
        />
      </View>
    </View>,
};
