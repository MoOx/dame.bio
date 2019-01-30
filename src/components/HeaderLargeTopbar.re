open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLargeTopbar");

let make = (~currentLocation, _children) => {
  ...component,
  render: _self =>
    <ContainerWithSpace
      wrapperStyle=Style.(
        style([backgroundColor(String(Consts.Colors.main))])
      )
      style=Style.(style([alignItems(Center)]))>
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
      <View style=Style.(style([alignItems(Center), flexDirection(Row)]))>
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
      </View>
    </ContainerWithSpace>,
  /* <View
       style=styles##row>
        <ViewLink style=styles##link href="/a-propos">
          {ReasonReact.string({j|À Propos|j})}
        </ViewLink>
        <ViewLink style=styles##link href="/univers">
          {ReasonReact.string({j|Univers du site|j})}
        </ViewLink>
        <ViewLink style=styles##link href="/colibri">
          {ReasonReact.string({j|Un colibri en action|j})}
        </ViewLink>
        <ViewLink style=styles##link href="/contact">
          {ReasonReact.string({j|Contact|j})}
        </ViewLink>
     </View> */
};
