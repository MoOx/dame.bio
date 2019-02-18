open Belt;
open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([
          justifyContent(Center),
          backgroundColor(String("#fefefe")),
          /* For the image on small screen */
          overflow(Hidden),
        ]),
      "content": style([alignItems(Center)]),
      "blocks": style([flexGrow(1.), flexShrink(0.), maxWidth(Pt(800.))]),
      "block": style([flex(1.), flexBasis(Pt(150.))]),
      "blockTitle":
        style([
          fontSize(Float(12.)),
          fontWeight(`_800),
          color(String(Consts.Colors.grey)),
          opacity(Float(0.75)),
        ]),
      "link":
        style([
          alignItems(Baseline),
          paddingVertical(Pt(Spacer.space /. 3.)),
          color(String(Consts.Colors.darkGrey)),
        ]),
      "footerCeption":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          // justifyContent(SpaceBetween),
        ]),
      "footerMinitem":
        style([flex(1.), alignItems(Center), flexBasis(Pt(250.))]),
      "copyright":
        style([
          fontSize(Float(12.)),
          color(String(Consts.Colors.darkGrey)),
        ]),
      "madeWith":
        style([
          fontSize(Float(12.)),
          color(String(Consts.Colors.darkGrey)),
        ]),
      "madeBy":
        style([
          fontSize(Float(12.)),
          color(String(Consts.Colors.darkGrey)),
        ]),
      "image": style([alignSelf(Center), flex(1.)]),
    },
  );

let component = ReasonReact.statelessComponent("Footer");

let uri = "/images/footer-flowers.png";
let width: Style.pt_only = Style.Pt(1800. *. 0.75);
let height: Style.pt_only = Style.Pt(324. *. 0.75);

let make = _children => {
  ...component,
  render: _self => {
    let year = "2019";
    <View style=styles##container>
      <Spacer size=XL />
      <InstagramFeed />
      <Spacer size=L />
      <View style=styles##content>
        <Container style=styles##blocks>
          <SpacedView
            style=Style.(
              concat([styles##block, style([alignItems(Center)])])
            )>
            <SVGDameBioLogo
              fill=Consts.Colors.alt
              width={20. *. 2.0}
              height={28. *. 2.0}
            />
          </SpacedView>
          <SpacedView style=styles##block>
            <Text style=styles##blockTitle>
              {{j|Catégories|j}->String.uppercase->ReasonReact.string}
            </Text>
            <Spacer />
            {Consts.categoriesLinks
             ->Array.map(l =>
                 <TextLink style=styles##link href={l.link} key={l.link}>
                   l.text->ReasonReact.string
                 </TextLink>
               )
             ->ReasonReact.array}
          </SpacedView>
          <SpacedView style=styles##block>
            <Text style=styles##blockTitle>
              {{j|Plus|j}->String.uppercase->ReasonReact.string}
            </Text>
            <Spacer />
            <TextLink style=styles##link href="/contact/">
              {j|Contact|j}->ReasonReact.string
            </TextLink>
            <TextLink style=styles##link href="/a-propos/">
              {j|À propos|j}->ReasonReact.string
            </TextLink>
            <TextLink style=styles##link href="/mentions-legales/">
              {j|Mentions légales|j}->ReasonReact.string
            </TextLink>
          </SpacedView>
          <SpacedView style=styles##block>
            <Text style=styles##blockTitle>
              {{j|Réseaux|j}->String.uppercase->ReasonReact.string}
            </Text>
            <Spacer />
            {Consts.socialLinks
             ->Array.map(item =>
                 <TextLink
                   style=styles##link
                   key={item.link}
                   href={item.link}
                   accessibilityLabel={item.text}>
                   {{item.title ++ "  "}->ReasonReact.string}
                   {item.componentFunc(~iconColor="#bbb", ~iconSize=12.)}
                 </TextLink>
               )
             ->ReasonReact.array}
          </SpacedView>
          <SpacedView style=styles##block />
        </Container>
        <div className="device-large"> <Spacer /> </div>
        <Spacer />
        <ContainerLarge style=styles##footerCeption>
          <SpacedView vertical=S style=styles##footerMinitem>
            <Text style=styles##copyright>
              {j|© 2009 · $year D'Âme Bio.\n    Tous droits réservés|j}
              ->ReasonReact.string
            </Text>
          </SpacedView>
          <SpacedView vertical=S style=styles##footerMinitem>
            <Text style=styles##madeWith>
              {j|Made with ♥ in France|j}->ReasonReact.string
            </Text>
          </SpacedView>
          <SpacedView vertical=S style=styles##footerMinitem>
            <Text style=styles##madeBy>
              {j|⭑ By |j}->ReasonReact.string
              <TextLink
                href="https://dame.bio/a-propos/"
                style=Style.(style([textDecorationLine(Underline)]))>
                {j|Liloue|j}->ReasonReact.string
              </TextLink>
              {j| & |j}->ReasonReact.string
              <TextLink
                href="https://moox.io/"
                style=Style.(style([textDecorationLine(Underline)]))>
                {j|MoOx|j}->ReasonReact.string
              </TextLink>
            </Text>
          </SpacedView>
        </ContainerLarge>
      </View>
      <Image
        style=styles##image
        source={`URI(Image.(imageURISource(~uri, ~width, ~height, ())))}
        defaultSource={
                        `URI(
                          Image.(defaultURISource(~uri, ~width, ~height, ())),
                        )
                      }
      />
    </View>;
  },
};
