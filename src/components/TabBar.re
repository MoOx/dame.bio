open ReactNative;

let colorInActive = Consts.Colors.tabBarIconInactive;
let colorActive = Consts.Colors.tabBarIconActive;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper":
        style(
          ~borderTopWidth=StyleSheet.hairlineWidth,
          ~borderColor="#E3E4E5",
          (),
        ),
      "container":
        style(
          ~flexDirection=`row,
          ~minHeight=50.->dp,
          ~alignItems=`center,
          (),
        ),
      "itemWrapper":
        style(~justifyContent=`center, ~width=(100. /. 6.)->pct, ()),
      "item": style(~justifyContent=`center, ~alignItems=`center, ()),
      "itemText":
        style(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~color=colorInActive,
          ~fontSize=10.,
          ~marginTop=1.5->dp,
          (),
        ),
      "itemTextActive": style(~color=colorActive, ()),
    })
  );

let width = 24.->Js.Float.toString;
let height = 24.->Js.Float.toString;

let renderItem = (~index as _, ~url, ~label, ~isActive) => {
  <ViewLink key=url href=url style=styles##itemWrapper>
    <View style=styles##item>
      {switch (url) {
       | "/" =>
         <SVGMenuHome
           width
           height
           fill={isActive ? colorActive : colorInActive}
         />
       | "/ateliers" =>
         <SVGMenuAteliers
           width
           height
           fill={isActive ? colorActive : colorInActive}
         />
       | "/alimentation" =>
         <SVGMenuRepas
           width
           height
           fill={isActive ? colorActive : colorInActive}
         />
       | "/yoga" =>
         <SVGMenuYoga
           width
           height
           fill={isActive ? colorActive : colorInActive}
         />
       | "/permaculture" =>
         <SVGMenuFeuilles
           width
           height
           fill={isActive ? colorActive : colorInActive}
         />
       | _ =>
         <SVGMore width height fill={isActive ? colorActive : colorInActive} />
       }}
      <Text
        style=Style.(
          arrayOption([|
            Some(styles##itemText),
            isActive ? Some(styles##itemTextActive) : None,
          |])
        )>
        label->React.string
      </Text>
    </View>
  </ViewLink>;
};

[@react.component]
let make = (~globals=?) => {
  let currentLocation = Next.useRouter().asPath;
  <SafeAreaView style=styles##wrapper>
    <View style=styles##container>
      {renderItem(
         ~index=1,
         ~url="/",
         ~label="Accueil",
         ~isActive=currentLocation == "/",
       )}
      <WpMenu
        menu=?{WpMenu.getMenu(globals, Consts.Menus.main)}
        renderItem
        currentLocation
        maxItems=4
      />
      {renderItem(~index=1, ~url="#footer", ~label="Plus", ~isActive=false)}
    </View>
  </SafeAreaView>;
};

let default = make;
