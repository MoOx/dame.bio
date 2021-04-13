open Belt
open ReactNative

let imageRatio = 240. /. 350.

let styles = {
  open Style
  StyleSheet.create({
    "block": style(~flexGrow=1., ~flexShrink=1., ~backgroundColor="#fff", ()),
    "metaRow": style(~flexDirection=#row, ~justifyContent=#spaceBetween, ()),
    "metaRowLeft": style(~flexDirection=#row, ~alignItems=#baseline, ()),
    "date": style(~fontSize=12., ~color=Consts.Colors.grey, ()),
    "categoryText": style(~fontSize=14., ~color=Consts.Colors.pink, ()),
    "actions": style(~flexDirection=#row, ~alignSelf=#flexEnd, ~alignItems=#center, ()),
    "action": style(~flexDirection=#row, ()),
    "actionText": style(~fontSize=10., ~color=ButtonLike.defaultColor, ()),
    "link": style(~padding=10.->dp, ()),
    "tags": style(~flexDirection=#row, ~flexWrap=#wrap, ~justifyContent=#center, ()),
    "tagText": style(~fontSize=16., ~lineHeight=29., ~color="#006579", ()),
  })
}

@react.component
let make = (~item: WPGraphQL.GetPagesAndPosts.GetPagesAndPosts_inner.t_pages_nodes, ()) =>
  <View style={styles["block"] /* accessibilityRole=`webAriaArticle */}>
    <SpacedView>
      <Heading>
        <span
          dangerouslySetInnerHTML={
            "__html": item.title->Option.getWithDefault(""),
          }
        />
      </Heading>
      <Spacer />
      <Html content=item.content />
    </SpacedView>
  </View>
