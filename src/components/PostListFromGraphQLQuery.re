open BsReactNative;
open Helpers;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "list":
        style([flexDirection(Row), flexWrap(Wrap), alignItems(FlexStart)]),
    },
  );

let component = ReasonReact.statelessComponent("PostListFromGraphQLQuery");

let make = (~items, _) => {
  ...component,
  render: _self =>
    <View style=styles##list>
      {
        items
        ->Belt.Array.map(item => {
            /* item
               ->Belt.Option.map(item => item##node)
               ->Belt.Option.map(item => <PostPreview key=item##id item />)
               ->Belt.Option.getWithDefault(nothing) */

            let node = [%get_in item#??node];
            switch (node) {
            | Some(item) => <PostPreviewFromGraphQLQuery key=item##id item />
            | None => nothing
            };
          })
        ->ReasonReact.array
      }
    </View>,
};
