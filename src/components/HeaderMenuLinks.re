open Belt;
open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderMenuLinks");

let textColor = Consts.Colors.light;

let styles =
  StyleSheet.create(
    Style.{
      "link":
        style([
          padding(Pt(10.)),
          fontSize(Float(14.)),
          lineHeight(14. *. 2.),
          color(String(textColor)),
        ]),
      "linkActive":
        style([textDecorationLine(Underline), textDecorationStyle(Solid)]),
    },
  );

let make = (~currentLocation, _children) => {
  ...component,
  render: _self =>
    <View style=Style.(style([flexDirection(Row)]))>
      {Consts.menuLinks
       /* ->Array.sliceToEnd(1) */
       ->Array.map(item => {
           let isActive = item.isActive(currentLocation##pathname, item.link);
           <TextLink
             key={item.link}
             href={item.link}
             style=Style.(
               concat([
                 styles##link,
                 isActive ? styles##linkActive : style([]),
               ])
             )>
             item.text->ReasonReact.string
           </TextLink>;
         })
       ->ReasonReact.array}
    </View>,
};
