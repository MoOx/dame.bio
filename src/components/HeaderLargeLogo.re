open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "background":
        style(
          ~width=100.->pct,
          ~padding=40.->dp,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~overflow=`hidden,
          (),
        ),
      "logo": style(~position=`relative, ~zIndex=1, ()),
      "logoImage": style(~justifyContent=`center, ~alignItems=`center, ()),
      "logoEffectWrapper":
        style(~position=`absolute, ~top=(-1.)->dp, ~left=50.->pct, ()),
      "logoEffect":
        style(
          ~left=(-5.)->pct,
          ~width=(685. *. 0.55)->dp,
          ~height=(290. *. 0.55)->dp,
          (),
        ),
      "words": style(~fontWeight=`_300, ~fontSize=16., ~color="#67B44B", ()),
      "wordsSep": style(~opacity=0.5, ()),
    })
  );

[@react.component]
let make = () => {
  <View style=styles##background>
    <Spacer />
    <ViewLink style=styles##logo href="/">
      <View style=styles##logoImage>
        <ImageFromUri
          resizeMode=`cover
          style=Style.(
            imageStyle(
              ~width=(727. *. 0.5)->dp,
              ~height=(292. *. 0.5)->dp,
              (),
            )
          )
          uri="/images/logo-dame.bio.jpg"
        />
      </View>
      // <SVGDameBioLogoText width=365. height=104. fill=Consts.Colors.alt />
      // <Spacer />
      // <SVGDameBioLogoSeparator
      //   width=145.
      //   height=27.
      //   fill=Consts.Colors.alt
      // />
      // <View style=styles##logoEffectWrapper>
      //   <ImageFromUri
      //     resizeMode=`cover
      //     style=styles##logoEffect
      //     uri="/images/logo-effect.png"
      //   />
      // </View>
      <View
        style=Style.(
          style(
            ~marginTop=20.->dp,
            ~justifyContent=`center,
            ~alignItems=`center,
            ~flexDirection=`row,
            (),
          )
        )>
        <Text style=styles##words> {j|Éveil|j}->React.string </Text>
        <Text style=styles##wordsSep>
          <SpacedView horizontal=XS>
            <SVGHeart width={48. *. 0.2} height={39. *. 0.2} />
          </SpacedView>
        </Text>
        <Text style=styles##words> "Conscience"->React.string </Text>
        <Text style=styles##wordsSep>
          <SpacedView horizontal=XS>
            <SVGHeart width={48. *. 0.2} height={39. *. 0.2} />
          </SpacedView>
        </Text>
        <Text style=styles##words> "Nature"->React.string </Text>
      </View>
    </ViewLink>
  </View>;
};
