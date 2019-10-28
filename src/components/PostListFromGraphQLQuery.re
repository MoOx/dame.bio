open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "list":
        style([flexDirection(Row), flexWrap(Wrap), alignItems(Stretch)]),
    })
  );

[@react.component]
let make = (~edges, ()) => {
  /* SpacedView for PostPreview background effect that overflow out of its container */
  <SpacedView vertical=S horizontal=None style=styles##list>
    {edges
     ->Array.mapWithIndex((index, edge) =>
         edge
         ->Option.flatMap(edge => edge##node)
         ->Option.map(item =>
             <PostPreviewFromGraphQLQuery
               key=item##id
               item
               withWatercolorBottomRightCorner={
                 index == Array.length(edges) - 1
               }
             />
           )
         ->Option.getWithDefault(React.null)
       )
     ->React.array}
    /* Avoid huge lonely items if we get an odd number of result */
    {Array.length(edges) mod 2 == 1
       ? <View style=PostPreviewFromGraphQLQuery.styles##wrapper />
       : React.null}
  </SpacedView>;
};
