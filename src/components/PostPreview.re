open BsReactNative;

include PostPreviewFromGraphQLQuery;

let component = ReasonReact.statelessComponent("PostPreview");

let make = (~item: Structures.post, _) => {
  ...component,
  render: _self => {
    let id = {
      Base64.encode("post:" ++ string_of_int(item.id));
    };
    let rootCategory = Structures.findRootCategory(item);
    let href =
      "/"
      ++ String.lowercase(rootCategory.slug)
      ++ "/"
      ++ String.lowercase(item.slug)
      ++ "/";
    let image =
      item.featuredMedia
      ->Belt.List.head
      ->Belt.Option.mapWithDefault(ReasonReact.null, media =>
          <ImageWithAspectRatio
            style=styles##image
            uri={media.media_details.sizes.medium.source_url}
            ratio=imageRatio
          />
        );
    let category = {
      String.uppercase(rootCategory.name)->ReasonReact.string;
    };
    let title = item.title;
    let likes = {
      switch (item.likes) {
      | 0 => ReasonReact.null
      | v => (v->string_of_int ++ "  ")->ReasonReact.string
      };
    };
    let comments = {
      (
        switch (item.comments) {
        | None => ""
        | Some(comments) => " " ++ Belt.List.length(comments)->string_of_int
        }
      )
      |> ReasonReact.string;
    };

    <SpacedView key=id style=styles##wrapper vertical=M horizontal=M>
      <ViewLink href style=styles##container>
        image
        <SpacedView vertical=M horizontal=M style=styles##text>
          <Text style=styles##categoryText> category </Text>
          <Spacer size=XS />
          <Text style=styles##titleText>
            <span dangerouslySetInnerHTML={"__html": title} />
          </Text>
        </SpacedView>
      </ViewLink>
      <SpacedView
        vertical=M
        horizontal=M
        style=styles##actionsWrapper
        pointerEvents=`boxNone>
        <PlaceholderWithAspectRatio ratio=imageRatio />
        <View style=styles##actions pointerEvents=`boxNone>
          <View style=styles##action>
            <View style=styles##actionWrapper>
              <Text style=styles##actionText> likes </Text>
              <ButtonLike id />
            </View>
          </View>
          <Text> "    "->ReasonReact.string </Text>
          <ViewLink style=styles##action href={href ++ "#comments"}>
            <View style=styles##actionWrapper>
              <SVGSpeechBubbleOutline
                fill=ButtonLike.defaultColor
                width=ButtonLike.defaultSize
                height=ButtonLike.defaultSize
              />
              <Text style=styles##actionText> comments </Text>
            </View>
          </ViewLink>
        </View>
      </SpacedView>
    </SpacedView>;
  },
};
