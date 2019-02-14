open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "list":
        style([flexDirection(Row), flexWrap(Wrap), alignItems(Stretch)]),
    },
  );

let component = ReasonReact.statelessComponent("PostListFromGraphQLQuery");

let make = (~edges, _) => {
  ...component,
  render: _self =>
    /* SpacedView for PostPreview background effect that overflow out of its container */
    <SpacedView vertical=S style=styles##list>
      {edges
       ->Array.mapWithIndex((index, edge) =>
           edge
           ->Option.flatMap(edge => edge##node)
           ->Option.map(item =>
               <PostPreviewFromGraphQLQuery
                 key=item##id
                 item
                 withFlowers={index == 0}
                 withWatercolorCorner={index == Array.length(edges) - 1}
               />
             )
           ->Option.getWithDefault(ReasonReact.null)
         )
       ->ReasonReact.array}
      /* Avoid huge lonely items if we get an odd number of result */
      {Array.length(edges) mod 2 == 1 ?
         <View style=PostPreviewFromGraphQLQuery.styles##wrapper /> :
         ReasonReact.null}
    </SpacedView>,
};
