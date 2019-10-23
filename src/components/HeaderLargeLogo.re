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
      "words":
        style([
          fontWeight(`_300),
          fontSize(Float(16.)),
          color(String("#67B44B")),
        ]),
      "wordsSep":
        style([
          fontWeight(`_100),
          fontSize(Float(10.)),
          color(String("#67B44B")),
          opacity(Float(0.5)),
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
      <View
        style=Style.(
          style([
            marginTop(Pt(20.)),
            justifyContent(Center),
            alignItems(Center),
            flexDirection(Row),
          ])
        )>
        <Text style=styles##words> {j|Éveil|j}->React.string </Text>
        <Text style=styles##wordsSep> {j|  ♥  |j}->React.string </Text>
        <Text style=styles##words> "Conscience"->React.string </Text>
        <Text style=styles##wordsSep> {j|  ♥  |j}->React.string </Text>
        <Text style=styles##words> "Nature"->React.string </Text>
      </View>
    </ViewLink>
  </View>;
};
