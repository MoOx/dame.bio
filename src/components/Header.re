open BsReactNative;

let component = ReasonReact.statelessComponent("Header");

let styles =
  StyleSheet.create(
    Style.(
      {
        "header":
          style([
            justifyContent(Center),
            alignItems(Center),
            marginBottom(Pt(60.))
          ]),
        "topbarWrapper": style([backgroundColor("#83A366")]),
        /* "topbar": style([flexDirection(Row), justifyContent(SpaceBetween)]), */
        "icons": style([flexDirection(Row)]),
        "topbarLinks": style([flexDirection(Row)]),
        "topbarLink":
          style([padding(Pt(10.)), fontSize(Float(12.)), color("#fff")]),
        "logo":
          style([
            fontFamily("IndieFlower"),
            fontWeight(`Bold),
            padding(Pt(60.)),
            fontSize(Float(64.)),
            textAlign(Center),
            color("#81B761")
          ]),
        "menu": style([maxWidth(Pt(1200.)), width(Pct(100.001))]),
        "menuLinks":
          style([
            display(Flex),
            flexDirection(Row),
            flexWrap(Wrap),
            justifyContent(SpaceBetween),
            paddingHorizontal(Pt(40.)),
            fontSize(Float(24.)),
            backgroundColor("#E5FCD0")
          ]),
        "menuLink":
          style([
            flex(1.),
            padding(Pt(12.)),
            fontFamily("IndieFlower"),
            fontWeight(`Bold),
            fontSize(Float(24.)),
            /* lineHeight(48.), */
            textAlign(Center),
            color("#587C43")
          ])
      }
    )
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##header>
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
      <View>
        <Text style=styles##logo>
          (ReasonReact.stringToElement({j|D'Âme Bio|j}))
        </Text>
      </View>
      <View style=styles##menu>
        <Text style=styles##menuLinks>
          <TextLink style=styles##menuLink href="/tag/permaculture">
            (ReasonReact.stringToElement({j|Permaculture|j}))
          </TextLink>
          <TextLink style=styles##menuLink href="/tag/cuisine">
            (ReasonReact.stringToElement({j|Cuisine|j}))
          </TextLink>
          <TextLink style=styles##menuLink href="/tag/bien-etre">
            (ReasonReact.stringToElement({j|Bien-être|j}))
          </TextLink>
          <TextLink style=styles##menuLink href="/tag/lifestyle">
            (ReasonReact.stringToElement({j|Lifestyle|j}))
          </TextLink>
          <TextLink style=styles##menuLink href="/tag/decouvertes">
            (ReasonReact.stringToElement({j|Découvertes|j}))
          </TextLink>
        </Text>
      </View>
    </View>
  /* <Container wrapperStyle=styles##topbarWrapper style=styles##topbar> */
};
