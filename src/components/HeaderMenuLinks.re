open Belt;
open BsReactNative;

let textColor = Consts.Colors.light;

let styles =
  Style.(
    StyleSheet.create({
      "link":
        style([
          padding(Pt(10.)),
          fontSize(Float(14.)),
          lineHeight(14. *. 2.),
          color(String(textColor)),
        ]),
      "linkActive":
        style([textDecorationLine(Underline), textDecorationStyle(Solid)]),
    })
  );

[@react.component]
let make = (~currentLocation, ()) => {
  <View style=Style.(style([flexDirection(Row)]))>
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
