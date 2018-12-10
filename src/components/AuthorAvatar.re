open BsReactNative;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.{
      "avatar":
        style([
          top(Pt(-10.)),
          left(Pt(-10.)),
          width(Pt(300.)),
          height(Pt(300.)),
        ]),
      "avatarDeco":
        style([
          paddingTop(Pt(30.)),
          paddingLeft(Pt(30.)),
          paddingBottom(Pt(25.)),
        ]),
      "avatarImage":
        style([
          /* opacity(Float(0.1)), */
          borderRadius(500.),
          width(Pct(100.)),
          paddingBottom(Pct(100.)),
        ]),
    },
  );

let uriBg = "/images/avatar-background.png";
let uri = "/images/avatar.jpg";

let make = _ => {
  ...component,
  render: _self =>
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
    </View>,
};
