open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderTopbar");

let styles =
  StyleSheet.create(
    Style.(
      {
        "topbarWrapper": style([backgroundColor("#7BA55F")]),
        "icons": style([flexDirection(Row)]),
        "topbarLinks": style([flexDirection(Row)]),
        "topbarLink":
          style([
            paddingVertical(Pt(6.)),
            paddingHorizontal(Pt(12.)),
            fontSize(Float(12.)),
            color("#fff")
          ])
      }
    )
  );

let make = _children => {
  ...component,
  render: _self =>
    <Container wrapperStyle=styles##topbarWrapper>
      <SocialIcons wrapperStyle=styles##icons iconStyle=styles##topbarLink />
      <View style=styles##topbarLinks>
        <TextLink style=styles##topbarLink href="/a-propos">
          (ReasonReact.stringToElement({j|À Propos|j}))
        </TextLink>
        <TextLink style=styles##topbarLink href="/univers">
          (ReasonReact.stringToElement({j|Univers du site|j}))
        </TextLink>
        <TextLink style=styles##topbarLink href="/colibri">
          (ReasonReact.stringToElement({j|Un colibri en action|j}))
        </TextLink>
        <TextLink style=styles##topbarLink href="/contact">
          (ReasonReact.stringToElement({j|Contact|j}))
        </TextLink>
      </View>
    </Container>
};
