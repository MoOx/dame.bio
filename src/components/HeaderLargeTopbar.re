open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLargeTopbar");

let make = (~currentLocation, _children) => {
  ...component,
  render: _self =>
    <ContainerWithSpace
      wrapperStyle=Style.(
        style([backgroundColor(String(Consts.Colors.main))])
      )
      style=Style.(style([justifyContent(SpaceBetween), width(Pct(100.))]))>
      <View style=Style.(style([alignItems(Center), flexDirection(Row)]))>
        <TextLink href="/">
          <SVGDameBioLogo
            fill=Consts.Colors.light
            width={20. *. 0.8}
            height={28. *. 0.8}
          />
        </TextLink>
        <Spacer />
        <HeaderMenuLinks currentLocation />
      </View>
      <SpacedView
        vertical=XS
        horizontal=None
        style=Style.(
          style([
            flexGrow(1.),
            flexShrink(1.),
            alignItems(Center),
            justifyContent(FlexEnd),
            flexDirection(Row),
          ])
        )>
        <SocialIcons
          wrapperStyle=Style.(
            style([alignItems(Center), flexDirection(Row)])
          )
          iconStyle=Style.(
            style([
              paddingVertical(Pt(6.)),
              paddingHorizontal(Pt(12.)),
              fontSize(Float(12.)),
              color(String("#fff")),
            ])
          )
        />
        <Spacer size=S />
        <SearchForm />
      </SpacedView>
    </ContainerWithSpace>,
};
