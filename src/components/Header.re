open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "header":
        viewStyle(
          ~borderTopColor=Consts.Colors.main,
          ~borderTopWidth=4.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#fefefe",
          ~overflow=`hidden,
          (),
        ),
      "backgroundImageWrapper":
        style(~position=`absolute, ~top=0.->dp, ~left=50.->pct, ()),

      "container": viewStyle(~flexDirection=`row, ()),
      "link":
        textStyle(
          ~padding=10.->dp,
          ~fontSize=14.,
          ~fontWeight=`_500,
          ~lineHeight=14. *. 2.,
          ~color=Consts.Colors.light,
          (),
        ),
      "linkActive":
        textStyle(
          ~textDecorationLine=`underline,
          ~textDecorationStyle=`solid,
          (),
        ),
      "logoContainer":
        style(
          ~width=100.->pct,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~overflow=`hidden,
          (),
        ),
      "logo": style(~position=`relative, ~zIndex=1, ()),
      "logoImage":
        style(
          ~justifyContent=`center,
          ~alignItems=`center,
          // ~maxWidth=100.->pct,
          (),
        ),
      "logoEffectWrapper":
        style(~position=`absolute, ~top=(-1.)->dp, ~left=50.->pct, ()),
      "logoEffect":
        style(
          ~left=(-5.)->pct,
          ~width=(685. *. 0.55)->dp,
          ~height=(290. *. 0.55)->dp,
          (),
        ),
      "baseline":
        style(
          ~flexGrow=1.,
          ~flexDirection=`row,
          ~justifyContent=`center,
          ~alignItems=`center,
          (),
        ),
      "baselineWord":
        style(~fontWeight=`_300, ~fontSize=16., ~color="#67B44B", ()),
      "baselineWordSmall":
        style(~fontWeight=`_300, ~fontSize=12., ~color="#67B44B", ()),
      "baselineSep": style(~opacity=0.5, ()),
    })
  );

let baselineSep =
  <Text style=styles##baselineSep>
    <SpacedView horizontal=XS>
      <SVGHeart width={48. *. 0.2} height={39. *. 0.2} />
    </SpacedView>
  </Text>;

[@react.component]
let make = (~currentLocation, ()) => {
  <View style=styles##header>
    <View style=styles##backgroundImageWrapper>
      <div className="device-small">
        <ImageFromUri
          resizeMode=`contain
          style=Style.(
            imageStyle(
              ~left=(-50.)->pct,
              ~width=(3387. *. 0.4)->dp,
              ~height=(394. *. 0.4)->dp,
              (),
            )
          )
          uri="/images/header-background.jpg"
        />
      </div>
      <div className="device-large">
        <ImageFromUri
          resizeMode=`contain
          style=Style.(
            imageStyle(
              ~left=(-50.)->pct,
              ~width=(3387. *. 0.5)->dp,
              ~height=(394. *. 0.5)->dp,
              (),
            )
          )
          uri="/images/header-background.jpg"
        />
      </div>
    </View>
    <ContainerWithSpace
      wrapperStyle=Style.(
        style(
          ~backgroundColor=Consts.Colors.main50,
          // cheating for small screen :)
          ~paddingLeft=(SpacedView.space /. 4.)->dp,
          ~paddingRight=(SpacedView.space /. 2.)->dp,
          (),
        )
      )
      style=Style.(
        style(
          ~justifyContent=`spaceBetween,
          ~width=100.->pct,
          ~flexGrow=1.,
          (),
        )
      )>
      {React.createElement(
         View.make,
         {
           "className": "device-large",
           "style":
             Style.(
               style(
                 ~alignItems=`center,
                 ~flexDirection=`row,
                 ~flexGrow=20.,
                 (),
               )
             ),
           "children":
             <>
               <TextLink href="/">
                 <SVGDameBioLogo
                   fill=Consts.Colors.light
                   width={20. *. 0.8}
                   height={28. *. 0.8}
                 />
               </TextLink>
               <Spacer />
               <View style=styles##container>
                 <WpMenu
                   id="TWVudTo5NTk="
                   currentLocation
                   renderItem={(~index as _, ~url, ~label, ~isActive) =>
                     <TextLink
                       key=url
                       href=url
                       style=Style.(
                         arrayOption([|
                           Some(styles##link),
                           isActive ? Some(styles##linkActive) : None,
                         |])
                       )>
                       label->React.string
                     </TextLink>
                   }
                 />
               </View>
             </>,
         }
         ->Obj.magic,
       )}
      <SpacedView
        vertical=XS
        horizontal=None
        style=Style.(
          style(
            ~flexGrow=1.,
            ~flexShrink=1.,
            ~alignItems=`center,
            ~justifyContent=`spaceBetween,
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
    </ContainerWithSpace>
    <View style=styles##logoContainer>
      <div className="device-small"> <Spacer size=L /> </div>
      <div className="device-large"> <Spacer size=XL /> </div>
      <ViewLink style=styles##logo href="/">
        <View style=styles##logoImage>
          <div className="device-small">
            <ImageFromUri
              resizeMode=`cover
              style=Style.(
                imageStyle(
                  ~width=(1080. *. 0.15)->dp,
                  ~height=(417. *. 0.15)->dp,
                  (),
                )
              )
              uri="/logo.jpg"
            />
          </div>
          <div className="device-large">
            <ImageFromUri
              resizeMode=`cover
              style=Style.(
                imageStyle(
                  ~width=(1080. *. 0.3)->dp,
                  ~height=(417. *. 0.3)->dp,
                  (),
                )
              )
              uri="/logo.jpg"
            />
          </div>
        </View>
        <div
          className="device-small"
          style={ReactDOMRe.Style.make(~textAlign="center", ())}>
          <View style=styles##baseline>
            <Text style=styles##baselineWordSmall>
              {j|Éveil|j}->React.string
            </Text>
            baselineSep
            <Text style=styles##baselineWordSmall>
              "Conscience"->React.string
            </Text>
            baselineSep
            <Text style=styles##baselineWordSmall>
              "Nature"->React.string
            </Text>
          </View>
        </div>
        <div className="device-large"> <Spacer size=S /> </div>
        <div
          className="device-large"
          style={ReactDOMRe.Style.make(~textAlign="center", ())}>
          <View style=styles##baseline>
            <Text style=styles##baselineWord>
              {j|Éveil|j}->React.string
            </Text>
            baselineSep
            <Text style=styles##baselineWord>
              "Conscience"->React.string
            </Text>
            baselineSep
            <Text style=styles##baselineWord> "Nature"->React.string </Text>
          </View>
        </div>
      </ViewLink>
      <div className="device-large"> <Spacer size=S /> </div>
    </View>
  </View>;
};
/* <HeaderLargeMenu /> */

let default = make;
