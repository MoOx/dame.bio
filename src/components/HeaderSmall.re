open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderSmall");

let styles =
  StyleSheet.create(
    Style.{
      "wrapper":
        style([
          flexDirection(Row),
          justifyContent(SpaceBetween),
          backgroundColor(String("#fff")),
          borderTopWidth(10.),
          borderColor(String("#006579")),
        ]),
      "logo":
        style([
          position(Relative),
          zIndex(1),
          paddingHorizontal(Pt(10.)),
          flex(1.),
        ]),
      "logoImage": style([]),
      "icons":
        style([
          flex(1.),
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "icon":
        style([
          flexGrow(1.),
          flexShrink(0.),
          display(Flex),
          alignItems(Center),
          padding(Pt(6.)),
          fontSize(Float(12.)),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <SpacedView vertical=M horizontal=XS style=styles##wrapper>
      <ViewLink style=styles##logo href="/">
        <SVGDameBioLogo
          width=150.
          height={140. /. 350. *. 150.}
          fill="#67B44B"
        />
      </ViewLink>
      <Spacer />
      <SocialIcons
        wrapperStyle=styles##icons
        iconStyle=styles##icon
        iconColor="#006579"
        iconSize=20.
      />
    </SpacedView>,
};
