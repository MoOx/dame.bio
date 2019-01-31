open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "list":
        style([flexDirection(Row), flexWrap(Wrap), alignItems(Stretch)]),
    },
  );

let component = ReasonReact.statelessComponent("PostList");

let make = (~posts, _) => {
  ...component,
  render: _self =>
    <View style=styles##list>
      {posts
       ->Belt.List.map((item: Structures.post) =>
           <PostPreview item key={string_of_int(item.id)} />
         )
       ->Belt.List.toArray
       ->ReasonReact.array}
    </View>,
};
