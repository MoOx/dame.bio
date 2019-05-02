open Belt;
open BsReactNative;

let colorInActive = Consts.Colors.tabBarIconInactive;
let colorActive = Consts.Colors.tabBarIconActive;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper":
        style([
          borderTopWidth(StyleSheet.hairlineWidth),
          borderColor(String("#E3E4E5")),
        ]),
      "container":
        style([
          flex(1.),
          flexDirection(Row),
          minHeight(Pt(50.)),
          alignItems(Center),
        ]),
      "itemWrapper": style([flex(1.), justifyContent(Center)]),
      "item": style([justifyContent(Center), alignItems(Center)]),
      "itemText":
        style([
          flex(1.),
          color(String(colorInActive)),
          fontSize(Float(10.)),
          marginTop(Pt(1.5)),
        ]),
      "itemTextActive": style([color(String(colorActive))]),
    })
  );

[@react.component]
let make = (~currentLocation, ()) => {
  <SafeAreaView style=styles##wrapper>
    <View style=styles##container>
      {Consts.tabBarLinks
       ->Array.map(item => {
           let isActive = item.isActive(currentLocation##pathname, item.link);
           <ViewLink
             key={item.link} href={item.link} style=styles##itemWrapper>
             <View style=styles##item>
               {item.icon(
                  ~width=24.,
                  ~height=24.,
                  ~fill=isActive ? colorActive : colorInActive,
                  (),
                )}
               <Text
                 style=Style.(
                   arrayOption([|
                     Some(styles##itemText),
                     isActive ? Some(styles##itemTextActive) : None,
                   |])
                 )>
                 item.text->React.string
               </Text>
             </View>
           </ViewLink>;
         })
       ->React.array}
    </View>
  </SafeAreaView>;
};

let default = make;
