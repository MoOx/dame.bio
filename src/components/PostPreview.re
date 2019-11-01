open Belt;
open ReactNative;

include PostPreviewFromGraphQLQuery;

[@react.component]
let make = (~item: Structures.post, ()) => {
  let id = Base64.encode("post:" ++ string_of_int(item.id));
  let rootCategory = Structures.findRootCategory(item);
  let href =
    "/"
    ++ String.lowercase(rootCategory.slug)
    ++ "/"
    ++ String.lowercase(item.slug)
    ++ "/";
  let image =
    item.featuredMedia
    ->List.head
    ->Option.mapWithDefault(React.null, media =>
        <ImageWithAspectRatio
          style=styles##image
          uri={media.media_details.sizes.medium.source_url}
          ratio=imageRatio
        />
      );
  let category = String.uppercase(rootCategory.name)->React.string;
  let title = item.title;
  let likes =
    switch (item.likes) {
    | 0 => React.null
    | v => (v->string_of_int ++ "  ")->React.string
    };
  let comments =
    (
      switch (item.comments) {
      | None => ""
      | Some(comments) => " " ++ List.length(comments)->string_of_int
      }
    )
    |> React.string;

  <SpacedView key=id style=styles##wrapper vertical=M horizontal=M>
    <ViewLink href style=styles##container>
      <View style=styles##containerContent>
        image
        <SpacedView vertical=M horizontal=M style=styles##text>
          <Text style=styles##categoryText> category </Text>
          <Spacer size=XS />
          <Text style=styles##titleText>
            <span dangerouslySetInnerHTML={"__html": title} />
          </Text>
        </SpacedView>
      </View>
    </ViewLink>
    <SpacedView
      vertical=M
      horizontal=M
      style=styles##actionsWrapper
      pointerEvents=`boxNone>
      <PlaceholderWithAspectRatio ratio=imageRatio />
      <View style=styles##actions pointerEvents=`boxNone>
        <View style=styles##action>
          <Text style=styles##actionText> likes </Text>
          <ButtonLike id />
        </View>
        <Text> "    "->React.string </Text>
        <ViewLink style=styles##action href={href ++ "#comments"}>
          <SVGSpeechBubbleOutline
            fill=ButtonLike.defaultColor
            width=ButtonLike.defaultSize
            height=ButtonLike.defaultSize
          />
          <Text style=styles##actionText> comments </Text>
        </ViewLink>
      </View>
    </SpacedView>
  </SpacedView>;
};
