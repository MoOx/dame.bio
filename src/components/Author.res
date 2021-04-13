open ReactNative

let styles = {
  open Style
  StyleSheet.create({
    "container": style(~flexDirection=#row, ~flexWrap=#wrap, ()),
    "block": style(~flexGrow=1., ~flexShrink=1., ~flexBasis=300.->dp, ()),
    "blockTitle": style(~fontSize=24., ~marginBottom=12.->dp, ~color=Consts.Colors.pink, ()),
    "blockText": style(~fontSize=16., ~lineHeight=16. *. 1.5, ()),
    "icons": style(~flexDirection=#row, ~justifyContent=#flexEnd, ()),
    "icon": style(),
    "iconWrapper": style(~zIndex=1, ~lineHeight=24., ~padding=14.->dp, ()),
    "iconBackground": style(~paddingTop=3.->dp, ~paddingRight=2.->dp, ()),
  })
}

let uriBg = "/images/avatar-background.png"
let uri = "/images/avatar.jpg"

@react.component
let make = () =>
  <View style={styles["container"]}>
    <AuthorAvatar />
    <Spacer />
    <View style={styles["block"]}>
      <Text style={styles["blockTitle"]}> {Consts.nickname->React.string} </Text>
      <Text style={styles["blockText"]}> <Bio> {Consts.bio->React.string} </Bio> </Text>
      <Spacer />
      <SocialIcons
        wrapperStyle={styles["icons"]}
        iconStyle={styles["icon"]}
        iconSize=24.
        iconWrapperFunc={(~children) =>
          <ImageBackgroundFromUri
            resizeMode=#cover style={styles["iconBackground"]} uri="/images/circle-splash-pink.png">
            <Text style={styles["iconWrapper"]}> children </Text>
          </ImageBackgroundFromUri>}
      />
    </View>
  </View>
