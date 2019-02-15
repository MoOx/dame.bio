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
      "block": style([flexBasis(Pt(200.))]),
      "link":
        style([
          color(String(Consts.Colors.darkGrey)),
          paddingVertical(Pt(Spacer.space /. 2.)),
        ]),
      "copyright":
        style([color(String(Consts.Colors.darkGrey)), fontWeight(`_300)]),
      "image": style([alignSelf(Center)]),
    },
  );

let component = ReasonReact.statelessComponent("Footer");

let uri = "/images/footer-flowers.png";
let width: Style.pt_only = Style.Pt(1800. *. 0.75);
let height: Style.pt_only = Style.Pt(324. *. 0.75);

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##container>
      <Spacer size=XL />
      <InstagramFeed />
      <Spacer size=L />
      <View style=styles##content>
        <Container>
          <SpacedView>
            <SVGDameBioLogo
              fill=Consts.Colors.alt
              width={20. *. 2.0}
              height={28. *. 2.0}
            />
          </SpacedView>
          <SpacedView style=styles##block>
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
            {Consts.socialLinks
             ->Array.map(item =>
                 <TextLink
                   style=styles##link
                   key={item.link}
                   href={item.link}
                   accessibilityLabel={item.text}>
                   item.title->ReasonReact.string
                 </TextLink>
               )
             ->ReasonReact.array}
          </SpacedView>
        </Container>
        <Spacer size=L />
        <Text style=styles##copyright>
          {j|Copyright © 2009 D'Âme Bio. Tous droits réservés.|j}
          ->ReasonReact.string
        </Text>
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
    </View>,
};
