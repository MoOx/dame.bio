open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          flex(1.),
          padding(Pt(20.)),
          borderColor(String("#F0F0EF")),
          backgroundColor(String("#fff")),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "metaRowLeft": style([flexDirection(Row), alignItems(Baseline)]),
      "date":
        style([fontSize(Float(12.)), color(String(Consts.Colors.grey))]),
      "categoryText":
        style([fontSize(Float(14.)), color(String("#DE6D88"))]),
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
    },
  );

let component = ReasonReact.statelessComponent("PageDetail");

let make = (~item, _) => {
  ...component,
  render: _self => {
    <ViewWeb style=styles##block accessibilityRole="article">
      <Heading>
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Option.getWithDefault(""),
          }
        />
      </Heading>
      <Spacer />
      <SpacedView> <Html content=item##content /> </SpacedView>
    </ViewWeb>;
  },
};
