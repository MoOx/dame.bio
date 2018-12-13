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

let make = (~edges, _) => {
  ...component,
  render: _self =>
    <View style=styles##list>
      {
        edges
        ->Belt.Array.map(edge =>
            edge
            ->Belt.Option.flatMap(edge => edge##node)
            ->Belt.Option.map(item =>
                <PostPreviewFromGraphQLQuery key=item##id item />
              )
            ->Belt.Option.getWithDefault(nothing)
          )
        ->ReasonReact.array
      }
    </View>,
};
