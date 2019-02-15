open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderSmall");

let styles =
  StyleSheet.create(
    Style.{
      "icons":
        style([
          flexShrink(1.),
          /* flex(1.), */
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "icon": style([padding(Pt(8.)), fontSize(Float(12.))]),
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
        horizontal=None style=Style.(style([flex(1.), alignItems(Center)]))>
        <SpacedView
          horizontal=XS
          vertical=None
          style=Style.(
            style([
              width(Pct(100.)),
              flexDirection(Row),
              justifyContent(SpaceBetween),
              alignItems(Center),
            ])
          )>
          <ViewLink
            style=Style.(
              style([
                position(Relative),
                zIndex(1),
                paddingHorizontal(Pt(10.)),
              ])
            )
            href="/">
            <SVGDameBioLogoText
              width={365. *. 0.35}
              height={104. *. 0.35}
              fill=Consts.Colors.alt
            />
          </ViewLink>
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
          fill=Consts.Colors.alt
        />
      </SpacedView>
    </View>,
};
