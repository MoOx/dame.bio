open Belt;
open ReactNative;

let textColor = Consts.Colors.light;

let styles =
  Style.(
    StyleSheet.create({
      "container": viewStyle(~flexDirection=`row, ()),
      "link":
        textStyle(
          ~padding=10.->dp,
          ~fontSize=14.,
          ~fontWeight=`_500,
          ~lineHeight=14. *. 2.,
          ~color=textColor,
          (),
        ),
      "linkActive":
        textStyle(
          ~textDecorationLine=`underline,
          ~textDecorationStyle=`solid,
          (),
        ),
    })
  );

[@react.component]
let make = (~currentLocation, ()) => {
  <View style=styles##container>
    {Consts.menuLinks
     ->Array.map(item => {
         let isActive = item.isActive(currentLocation##pathname, item.link);
         <TextLink
           key={item.link}
           href={item.link}
           style=Style.(
             arrayOption([|
               Some(styles##link),
               isActive ? Some(styles##linkActive) : None,
             |])
           )>
           item.text->React.string
         </TextLink>;
       })
     ->React.array}
  </View>;
};
