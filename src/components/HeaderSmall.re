open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderSmall");

let styles =
  StyleSheet.create(
    Style.{
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
          padding(Pt(8.)),
          fontSize(Float(12.)),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=Style.(style([backgroundColor(String("#fff"))]))>
      <View
        style=Style.(
          style([
            width(Pct(100.)),
            height(Pt(10.)),
            backgroundColor(String("#006579")),
          ])
        )
      />
      <SpacedView
        vertical=M style=Style.(style([flex(1.), alignItems(Center)]))>
        <SpacedView
          horizontal=XS
          style=Style.(
            style([
              width(Pct(100.)),
              flexDirection(Row),
              justifyContent(SpaceBetween),
              alignItems(Center),
            ])
          )>
          <ViewLink style=styles##logo href="/">
            <SVGDameBioLogoText
              width={365. *. 0.4}
              height={104. *. 0.4}
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
        </SpacedView>
        <Spacer size=S />
        <SVGDameBioLogoSeparator
          width={145. *. 0.8}
          height={27. *. 0.8}
          fill="#67B44B"
        />
      </SpacedView>
    </View>,
};
