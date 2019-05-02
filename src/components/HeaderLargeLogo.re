open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
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
      "logoImage": style([justifyContent(Center), alignItems(Center)]),
      "logoEffectWrapper":
        style([position(Absolute), top(Pt(-15.)), left(Pct(50.))]),
      "logoEffect":
        style([
          left(Pct(-50.)),
          width(Pt(685. *. 0.55)),
          height(Pt(290. *. 0.55)),
        ]),
    })
  );

[@react.component]
let make = () => {
  <View style=styles##background>
    <View style=styles##backgroundImageWrapper>
      <ImageFromUri
        resizeMode=`contain
        style=styles##backgroundImage
        uri="/images/header-background.png"
      />
    </View>
    <Spacer />
    <ViewLink style=styles##logo href="/">
      <View style=styles##logoImage>
        <SVGDameBioLogoText width=365. height=104. fill=Consts.Colors.alt />
        <Spacer />
        <SVGDameBioLogoSeparator
          width=145.
          height=27.
          fill=Consts.Colors.alt
        />
      </View>
      <View style=styles##logoEffectWrapper>
        <ImageFromUri
          resizeMode=`cover
          style=styles##logoEffect
          uri="/images/logo-effect.png"
        />
      </View>
    </ViewLink>
  </View>;
};
