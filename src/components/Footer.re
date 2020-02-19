open Belt;
open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style([
          justifyContent(Center),
          backgroundColor(String("#fefefe")),
          /* For the image on small screen */
          overflow(Hidden),
        ]),
      "content": style([alignItems(Center)]),
      "blocks": style([flexGrow(1.), flexShrink(0.), maxWidth(Pt(800.))]),
      "block": style([flexGrow(1.), flexShrink(1.), flexBasis(Pt(150.))]),
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
      "footerCeption": style([flexDirection(Row), flexWrap(Wrap)]),
      "footerMinitem":
        style([
          flexGrow(1.),
          flexShrink(1.),
          alignItems(Center),
          flexBasis(Pt(250.)),
        ]),
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
    })
  );

let uri = "/images/footer-flowers.png";
let width: Style.pt_only = Style.Pt(1800. *. 0.75);
let height: Style.pt_only = Style.Pt(324. *. 0.75);

let renderItem = (~index as _, ~url, ~label, ~isActive as _) => {
  <TextLink style=styles##link href=url key=url>
    label->React.string
  </TextLink>;
};

[@react.component]
let make = () => {
  let year =
    Js.Date.now()->Js.Date.fromFloat->Js.Date.getFullYear->Js.Float.toString;
  <View style=styles##container>
    <Spacer size=XL />
    <ViewportObserver>
      ...{state => state##hasBeenVisible ? <InstagramFeed /> : React.null}
    </ViewportObserver>
    <Spacer size=L />
    <div id="footer" />
    <SpacedView style=styles##content>
      <Container style=styles##blocks>
        <SpacedView
          style=Style.(
            array([|styles##block, style([alignItems(Center)])|])
          )>
          <SVGDameBioLogo
            fill=Consts.Colors.alt
            width={20. *. 2.0}
            height={28. *. 2.0}
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Catégories|j}->String.uppercase->React.string}
          </Text>
          <Spacer />
          <WpMenu
            id=Consts.Menus.categories
            currentLocation={"pathname": ""}
            renderItem
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Plus|j}->String.uppercase->React.string}
          </Text>
          <Spacer />
          <WpMenu
            id=Consts.Menus.more
            currentLocation={"pathname": ""}
            renderItem
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Réseaux|j}->String.uppercase->React.string}
          </Text>
          <Spacer />
          {Consts.socialLinks
           ->Array.map(item =>
               <TextLink
                 style=styles##link
                 key={item.link}
                 href={item.link}
                 accessibilityLabel={item.text}>
                 {(item.title ++ "  ")->React.string}
                 {item.componentFunc(~iconColor="#bbb", ~iconSize=12.)}
               </TextLink>
             )
           ->React.array}
        </SpacedView>
        <Spacer style=styles##block />
      </Container>
      <div className="device-large"> <Spacer size=L /> </div>
      <ContainerLarge style=styles##footerCeption>
        <SpacedView vertical=S style=styles##footerMinitem>
          <Text style=styles##copyright>
            {j|© 2009 · $year D'Âme Bio.\n    Tous droits réservés|j}
            ->React.string
          </Text>
        </SpacedView>
        <SpacedView vertical=S style=styles##footerMinitem>
          <Text style=styles##madeWith>
            {j|Made with ♥ in France|j}->React.string
          </Text>
        </SpacedView>
        <SpacedView vertical=S style=styles##footerMinitem>
          <Text style=styles##madeBy>
            <LoginForm />
            {j| By |j}->React.string
            <TextLink
              href={Consts.frontendUrl ++ "/a-propos/"}
              style=Style.(style([textDecorationLine(Underline)]))>
              Consts.nickname->React.string
            </TextLink>
            {j| & |j}->React.string
            <TextLink
              href="https://moox.io/"
              style=Style.(style([textDecorationLine(Underline)]))>
              {j|MoOx|j}->React.string
            </TextLink>
          </Text>
        </SpacedView>
      </ContainerLarge>
    </SpacedView>
    <div className="device-small"> <Spacer size=L /> </div>
    <div
      className="device-large"
      style={ReactDOMRe.Style.make(~alignSelf="center", ~flex="1", ())}>
      <Image
        style=styles##image
        source={`URI(Image.(imageURISource(~uri, ~width, ~height, ())))}
        defaultSource={
                        `URI(
                          Image.(defaultURISource(~uri, ~width, ~height, ())),
                        )
                      }
      />
    </div>
  </View>;
};
