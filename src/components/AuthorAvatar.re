open BsReactNative;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.{
      "avatar": style([width(Pt(256.)), height(Pt(256.))]),
      "avatarDeco":
        style([
          position(Absolute),
          left(Pt(-35.)),
          top(Pt(-30.)),
          right(Pt(-10.)),
          bottom(Pt(-20.)),
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
        defaultSource={`URI(Image.(defaultURISource(~uri=uriBg, ())))}
      />
      <Image
        style=styles##avatarImage
        source={`URI(Image.(imageURISource(~uri, ())))}
        /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
        defaultSource={`URI(Image.(defaultURISource(~uri, ())))}
      />
    </View>,
};
