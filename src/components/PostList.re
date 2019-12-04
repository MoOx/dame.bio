open Belt;
open ReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "list":
        style(~flexDirection=`row, ~flexWrap=`wrap, ~alignItems=`stretch, ()),
    })
  );

[@react.component]
let make = (~nodes, ()) => {
  /* SpacedView for PostPreview background effect that overflow out of its container */
  <SpacedView vertical=S horizontal=None style=styles##list>
    {nodes
     ->Array.mapWithIndex((index, node) =>
         node
         ->Option.map(item =>
             <PostPreview
               key=item##id
               item
               withWatercolorBottomRightCorner={
                 index == Array.length(nodes) - 1
               }
             />
           )
         ->Option.getWithDefault(React.null)
       )
     ->React.array}
    /* Avoid huge lonely items if we get an odd number of result */
    {Array.length(nodes) mod 2 == 1
       ? <View style=PostPreview.styles##wrapper /> : React.null}
  </SpacedView>;
};
