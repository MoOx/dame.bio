open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLargeLogo");

let styles =
  StyleSheet.create(
    Style.{
      "background":
        style([
          width(Pct(100.)),
          padding(Pt(40.)),
          justifyContent(Center),
          alignItems(Center),
          overflow(Hidden),
        ]),
      "backgroundImageWrapper":
        style([position(Absolute), top(Pt(0.)), left(Pct(50.))]),
      "backgroundImage":
        style([
          left(Pct(-50.)),
          width(Pt(2523. *. 0.5)),
          height(Pt(163. *. 0.5)),
        ]),
      "logo": style([position(Relative), zIndex(1)]),
      "logoImage": style([]),
      "logoEffectWrapper":
        style([position(Absolute), top(Pt(-15.)), left(Pct(50.))]),
      "logoEffect":
        style([
          left(Pct(-50.)),
          width(Pt(685. *. 0.55)),
          height(Pt(290. *. 0.55)),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##background>
      <View style=styles##backgroundImageWrapper>
        <ImageFromUri
          resizeMode=`contain
          style=styles##backgroundImage
          uri="/images/header-background.png"
        />
      </View>
      <Spacer />
      <TouchableScaleLink
        style=styles##logo href="/" activeScale=0.98 friction=5. tension=20.>
        <View style=styles##logoImage>
          <SVGDameBioLogo width=350. height=140. fill="#67B44B" />
        </View>
        <View style=styles##logoEffectWrapper>
          <ImageFromUri
            resizeMode=`cover
            style=styles##logoEffect
            uri="/images/logo-effect.png"
          />
        </View>
      </TouchableScaleLink>
    </View>,
};
