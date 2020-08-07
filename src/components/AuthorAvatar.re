open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "avatar": style(~width=256.->dp, ~height=256.->dp, ()),
      "avatarDeco":
        style(
          ~position=`absolute,
          ~left=(-35.)->dp,
          ~top=(-30.)->dp,
          ~right=(-10.)->dp,
          ~bottom=(-20.)->dp,
          (),
        ),
      "avatarImage":
        style(
          /* ~opacity=0.1, */
          ~borderRadius=Consts.Radius.avatarBig,
          ~width=100.->pct,
          ~paddingBottom=100.->pct,
          (),
        ),
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
