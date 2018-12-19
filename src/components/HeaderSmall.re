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
        ]),
      "logoImage": style([]),
      "icons": style([flexDirection(Row)]),
      "icon":
        style([
          display(Flex),
          alignItems(Center),
          paddingVertical(Pt(6.)),
          paddingHorizontal(Pt(12.)),
          fontSize(Float(12.)),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <SpacedView vertical=M horizontal=S style=styles##wrapper>
      <TextLink style=styles##logo href="/">
        <SVGDameBioLogo
          width=150.
          height={140. /. 350. *. 150.}
          fill="#67B44B"
        />
      </TextLink>
      <SocialIcons
        wrapperStyle=styles##icons
        iconStyle=styles##icon
        iconColor="#006579"
        iconSize=20.
      />
    </SpacedView>,
};
