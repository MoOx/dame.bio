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
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~flexDirection=`row,
          ~minHeight=50.->dp,
          ~alignItems=`center,
          (),
        ),
      "itemWrapper":
        style(~flexGrow=1., ~flexShrink=1., ~justifyContent=`center, ()),
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

let renderItem = (~index, ~url, ~label, ~isActive) => {
  index > 2
    ? React.null
    : <ViewLink key=url href=url style=styles##itemWrapper>
        <View style=styles##item>
          {switch (url) {
           | "/" =>
             <SVGMenuHome
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
           | "/ateliers/" =>
             <SVGMenuAteliers
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
           | "/alimentation/" =>
             <SVGMenuRepas
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
           | "/yoga/" =>
             <SVGMenuYoga
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
           | "/permaculture/" =>
             <SVGMenuFeuilles
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
           | _ =>
             <SVGMore
               width
               height
               fill={isActive ? colorActive : colorInActive}
             />
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
let make = (~currentLocation, ()) => {
  <SafeAreaView style=styles##wrapper>
    <View style=styles##container>
      {renderItem(
         ~index=1,
         ~url="/",
         ~label="Accueil",
         ~isActive=currentLocation##pathname == "/",
       )}
      <WpMenu id=Consts.Menus.main currentLocation renderItem />
      {renderItem(~index=1, ~url="#footer", ~label="Plus", ~isActive=false)}
    </View>
  </SafeAreaView>;
};

let default = make;
