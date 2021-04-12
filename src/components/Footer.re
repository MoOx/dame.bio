open Belt;
open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(
          ~justifyContent=`center,
          ~backgroundColor="#fefefe",
          /* For the image on small screen */
          ~overflow=`hidden,
          (),
        ),
      "content": style(~alignItems=`center, ()),
      "blocks": style(~flexGrow=1., ~flexShrink=0., ~maxWidth=800.->dp, ()),
      "block": style(~flexGrow=1., ~flexShrink=1., ~flexBasis=150.->dp, ()),
      "blockTitle":
        style(
          ~fontSize=12.,
          ~fontWeight=`_800,
          ~color=Consts.Colors.grey,
          ~opacity=0.75,
          (),
        ),
      "link":
        style(
          ~alignItems=`baseline,
          ~paddingVertical=(Spacer.space /. 3.)->dp,
          ~color=Consts.Colors.darkGrey,
          (),
        ),
      "footerCeption": style(~flexDirection=`row, ~flexWrap=`wrap, ()),
      "footerMinitem":
        style(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~alignItems=`center,
          ~flexBasis=250.->dp,
          (),
        ),
      "copyright": style(~fontSize=12., ~color=Consts.Colors.darkGrey, ()),
      "madeWith": style(~fontSize=12., ~color=Consts.Colors.darkGrey, ()),
      "madeBy": style(~fontSize=12., ~color=Consts.Colors.darkGrey, ()),
      "image": style(~alignSelf=`center, ~flex=1., ()),
    })
  );

let uri = "/images/footer-flowers.png";
let width = 1800. *. 0.75;
let height = 324. *. 0.75;

let renderItem = (~index as _, ~url, ~label, ~isActive as _) => {
  <TextLink style=styles##link href=url key=url>
    label->React.string
  </TextLink>;
};

let isClient: bool = [%raw "typeof window !== \"undefined\""];

[@react.component]
let make = (~globals=?, ~currentLocation) => {
  let year =
    Js.Date.now()->Js.Date.fromFloat->Js.Date.getFullYear->Js.Float.toString;
  <View style=styles##container>
    <Spacer size=XL />
    <div id="footer" />
    <SpacedView style=styles##content>
      <Container style=styles##blocks>
        <SpacedView
          style=Style.(
            array([|styles##block, style(~alignItems=`center, ())|])
          )>
          <SVGDameBioLogo
            fill=Consts.Colors.alt
            width={(20. *. 2.0)->Js.Float.toString}
            height={(28. *. 2.0)->Js.Float.toString}
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Catégories|j}->Js.String.toUpperCase->React.string}
          </Text>
          <Spacer />
          <WpMenu
            menu=?{WpMenu.getMenu(globals, Consts.Menus.categories)}
            renderItem
            currentLocation
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Plus|j}->Js.String.toUpperCase->React.string}
          </Text>
          <Spacer />
          <WpMenu
            menu=?{WpMenu.getMenu(globals, Consts.Menus.more)}
            renderItem
            currentLocation
          />
        </SpacedView>
        <SpacedView style=styles##block>
          <Text style=styles##blockTitle>
            {{j|Réseaux|j}->Js.String.toUpperCase->React.string}
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
            // <LoginForm />

              {j| By |j}->React.string
              <TextLink
                href={Consts.frontendUrl ++ "/a-propos/"}
                style=Style.(style(~textDecorationLine=`underline, ()))>
                Consts.nickname->React.string
              </TextLink>
              {j| & |j}->React.string
              <TextLink
                href="https://moox.io/"
                style=Style.(style(~textDecorationLine=`underline, ()))>
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
        source=Image.(
          Source.fromUriSource(uriSource(~uri, ~width, ~height, ()))
        )
        // SSR workaround https://github.com/necolas/react-native-web/issues/543
        defaultSource={Image.DefaultSource.fromUri(~uri, ~width, ~height, ())}
      />
    </div>
  </View>;
};
