open BsReactNative;

let component = ReasonReact.statelessComponent("PostPreview");

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          flex(1.),
          flexBasis(Pt(340.)),
          borderWidth(0.75),
          borderColor(String("#EBEBEB")),
          backgroundColor(String("#FFF")),
        ]),
      "row": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "text": style([padding(Pt(20.))]),
      "category":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(10.)),
          color(String("#DE6D88")),
        ]),
      "actions":
        style([
          display(Flex),
          flexDirection(Row),
          marginBottom(Pt(10.)),
          fontSize(Float(10.)),
          color(String("#bbb")),
        ]),
      "action":
        style([
          display(Flex),
          flexDirection(Row),
          marginHorizontal(Pt(4.)),
        ]),
      "title":
        style([
          fontSize(Float(22.)),
          fontWeight(`_300),
          lineHeight(28.),
          color(String("#1C1C1C")),
        ]),
      "link": style([padding(Pt(10.))]),
    },
  );

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
    <SpacedView
      key={string_of_int(item.id)}
      style=styles##block
      vertical=M
      horizontal=M>
      <TextLink href>
        {switch (Belt.List.head(item.featuredMedia)) {
         | Some(media) =>
           <ImageWithAspectRatio
             uri={media.media_details.sizes.medium.source_url}
           />
         | None => ReasonReact.null
         }}
      </TextLink>
      <View style=styles##text>
        <View style=styles##row>
          <TextLink
            style=styles##category
            href={"/" ++ Utils.encodeURI(rootCategory.slug) ++ "/"}>
            {String.uppercase(rootCategory.name)->ReasonReact.string}
          </TextLink>
          <Text style=styles##actions>
            <TextLink style=styles##action href="#like">
              <SVGFavorite fill="#ddd" width=12. height=12. />
              (
                if (item.likes != 0) {
                  " " ++ (item.likes |> string_of_int);
                } else {
                  "";
                }
              )
              ->ReasonReact.string
            </TextLink>
            <Text style=styles##action> " | "->ReasonReact.string </Text>
            <TextLink style=styles##action href={href ++ "#comments"}>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
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
    </SpacedView>;
  },
};
