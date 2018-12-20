open BsReactNative;

include PostPreviewFromGraphQLQuery;

let component = ReasonReact.statelessComponent("PostPreview");

let make = (~item: Structures.post, _) => {
  ...component,
  render: _self => {
    let rootCategory = Structures.findRootCategory(item);
    let href =
      "/"
      ++ String.lowercase(rootCategory.slug)
      ++ "/"
      ++ String.lowercase(item.slug)
      ++ "/";
    <SpacedView style=styles##wrapper vertical=M horizontal=M>
      <View style=styles##container>
        <TextLink href>
          {item.featuredMedia
           ->Belt.List.head
           ->Belt.Option.mapWithDefault(ReasonReact.null, media =>
               <ImageWithAspectRatio
                 style=styles##image
                 uri={media.media_details.sizes.medium.source_url}
               />
             )}
        </TextLink>
        <View style=styles##text>
          <View style=styles##row>
            <TextLink
              style=styles##category
              href={"/" ++ Utils.encodeURI(rootCategory.slug) ++ "/"}>
              {String.uppercase(rootCategory.name)->ReasonReact.string}
            </TextLink>
            <Text style=styles##actions>
              {switch (item.likes) {
               | 0 => ReasonReact.null
               | v => (v->string_of_int ++ "  ")->ReasonReact.string
               }}
              <ButtonLike
                id={Base64.encode("post:" ++ string_of_int(item.id))}
              />
              <Text> "    "->ReasonReact.string </Text>
              <TextLink style=styles##action href={href ++ "#comments"}>
                <SVGSpeechBubbleOutline
                  fill=ButtonLike.defaultColor
                  width=ButtonLike.defaultSize
                  height=ButtonLike.defaultSize
                />
                {(
                   switch (item.comments) {
                   | None => ""
                   | Some(comments) =>
                     " " ++ Belt.List.length(comments)->string_of_int
                   }
                 )
                 |> ReasonReact.string}
              </TextLink>
            </Text>
          </View>
          <TextLink style=styles##title href>
            <span dangerouslySetInnerHTML={"__html": item.title} />
          </TextLink>
        </View>
      </View>
    </SpacedView>;
  },
};
