open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
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
    })
  );

let uriBg = "/images/avatar-background.png";
let uri = "/images/avatar.jpg";

[@react.component]
let make = () => {
  <View style=styles##avatar>
    <ImageFromUri resizeMode=`contain style=styles##avatarDeco uri=uriBg />
    <ImageFromUri style=styles##avatarImage uri />
  </View>;
};
