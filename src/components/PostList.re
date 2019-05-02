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
let make = (~posts, ()) => {
  <View style=styles##list>
    {posts
     ->List.map((item: Structures.post) =>
         <PostPreview item key={string_of_int(item.id)} />
       )
     ->List.toArray
     ->React.array}
  </View>;
};
