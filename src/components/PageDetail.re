open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "block":
        style([
          flexGrow(1.),
          flexShrink(1.),
          backgroundColor(String("#fff")),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "metaRowLeft": style([flexDirection(Row), alignItems(Baseline)]),
      "date":
        style([fontSize(Float(12.)), color(String(Consts.Colors.grey))]),
      "categoryText":
        style([fontSize(Float(14.)), color(String(Consts.Colors.pink))]),
      "actions":
        style([
          flexDirection(Row),
          alignSelf(FlexEnd),
          alignItems(Center),
        ]),
      "action": style([flexDirection(Row)]),
      "actionText":
        style([
          fontSize(Float(10.)),
          color(String(ButtonLike.defaultColor)),
        ]),
      "link": style([padding(Pt(10.))]),
      "tags":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "tagText":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          color(String("#006579")),
        ]),
    })
  );

[@react.component]
let make = (~item, ()) => {
  <View style=styles##block /*accessibilityRole=`webAriaArticle*/>
    <SpacedView>
      <Heading>
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Option.getWithDefault(""),
          }
        />
      </Heading>
      <Spacer />
      <Html content=item##content />
    </SpacedView>
  </View>;
};
