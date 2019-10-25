open ReactNative;

[@react.component]
let make = (~currentLocation, ()) => {
  <ContainerWithSpace
    wrapperStyle=Style.(
      style(
        ~borderTopColor=Consts.Colors.main,
        ~borderTopWidth=4.,
        ~backgroundColor=Consts.Colors.main50,
        (),
      )
    )
    style=Style.(style(~justifyContent=`spaceBetween, ~width=100.->pct, ()))>
    <View style=Style.(style(~alignItems=`center, ~flexDirection=`row, ()))>
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
        style(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~alignItems=`center,
          ~justifyContent=`flexEnd,
          ~flexDirection=`row,
          (),
        )
      )>
      <SocialIcons
        wrapperStyle=Style.(
          style(~alignItems=`center, ~flexDirection=`row, ())
        )
        iconStyle=Style.(
          style(
            ~paddingVertical=6.->dp,
            ~paddingHorizontal=12.->dp,
            ~fontSize=12.,
            ~color="#fff",
            (),
          )
        )
      />
      <Spacer size=S />
      <SearchForm />
    </SpacedView>
  </ContainerWithSpace>;
};
