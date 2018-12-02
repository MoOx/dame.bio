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

let component = ReasonReact.statelessComponent("PostList");

let make = (~items, _) => {
  ...component,
  render: _self =>
    <View style=styles##list>
      {
        items
        ->Belt.List.map(item =>
            switch ([%get_in item#??node]) {
            | Some(item) => <PostPreview key=item##id item />
            | None => nothing
            }
          )
        ->Belt.List.toArray
        ->ReasonReact.array
      }
    </View>,
};
