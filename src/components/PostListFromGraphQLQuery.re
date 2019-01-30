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
       ->Belt.Array.mapWithIndex((index, edge) =>
           edge
           ->Belt.Option.flatMap(edge => edge##node)
           ->Belt.Option.map(item =>
               <PostPreviewFromGraphQLQuery
                 key=item##id
                 item
                 withFlowers={index == 0}
                 withWatercolorCorner={index == Belt.Array.length(edges) - 1}
               />
             )
           ->Belt.Option.getWithDefault(ReasonReact.null)
         )
       ->ReasonReact.array}
    </SpacedView>,
};
