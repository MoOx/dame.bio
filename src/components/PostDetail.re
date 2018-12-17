open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          flex(1.),
          padding(Pt(20.)),
          borderColor(String("#F0F0EF")),
          backgroundColor(String("#fff")),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "tags":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "tag":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          color(String("#006579")),
        ]),
      "category": style([fontSize(Float(14.)), color(String("#DE6D88"))]),
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
          marginBottom(Pt(10.)),
          fontSize(Float(32.)),
          lineHeight(32. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
      "link": style([padding(Pt(10.))]),
    },
  );

let component = ReasonReact.statelessComponent("PostDetail");

let make = (~item, _) => {
  ...component,
  render: _self => {
    let rootCategory =
      T.getMainCategory(
        item##categories
        ->Belt.Option.flatMap(cs => cs##nodes)
        ->Belt.Option.getWithDefault([||]),
      );
    let href =
      "/"
      ++ rootCategory##slug->Belt.Option.getWithDefault("_")
      ++ "/"
      ++ item##slug->Belt.Option.getWithDefault(item##id)
      ++ "/";
    <View style=styles##block>
      <Text style=styles##title>
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Belt.Option.getWithDefault(""),
          }
        />
      </Text>
      <View style=styles##metaRow>
        <TextLink
          style=styles##category
          href={
            "/"
            ++ Utils.encodeURI(
                 rootCategory##slug->Belt.Option.getWithDefault("_"),
               )
            ++ "/"
          }>
          {String.uppercase(
             rootCategory##name->Belt.Option.getWithDefault(""),
           )
           ->ReasonReact.string}
        </TextLink>
        <Text style=styles##actions>
          <Text style=styles##actions>
            <ButtonLike id=item##id />
            {switch (item##likeCount->Belt.Option.getWithDefault(0)) {
             | 0 => ReasonReact.null
             | v => ("  " ++ v->string_of_int)->ReasonReact.string
             }}
            <Text style=styles##action> " | "->ReasonReact.string </Text>
            <TextLink style=styles##action href={href ++ "#comments"}>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
              {switch (item##commentCount->Belt.Option.getWithDefault(0)) {
               | 0 => ReasonReact.null
               | v => ("  " ++ v->string_of_int)->ReasonReact.string
               }}
            </TextLink>
          </Text>
        </Text>
      </View>
      <SpacedView vertical=M>
        <div
          className="dbPost"
          dangerouslySetInnerHTML={
            "__html":
              Js.String.replaceByRe(
                [%re "/=\"\\/wp-content/g"],
                "=\"https://dame.bio/wp-content",
                Js.String.replaceByRe(
                  [%re "/\\u2b50\\ufe0e(<br \\/>?)/g"],
                  ""
                  ++ "<span style=\"display: block; text-align: center; margin: 40px;\">"
                  ++ "<span style=\"display: inline-block;background: url(/images/line_flower.png) no-repeat; height: 14px; width: 68px;\"></span>"
                  /* ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-left.png) no-repeat; height: 21px; width: 17px;\"></span>"
                     ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-tile.png) repeat-x; height: 21px; width: 80%;\"></span>"
                     ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-right.png) no-repeat; height: 21px; width: 66px;\"></span>" */
                  ++ "</span>",
                  item##content->Belt.Option.getWithDefault(""),
                ),
              ),
          }
        />
      </SpacedView>
      <SpacedView vertical=L style=styles##tags>
        {item##tags
         ->Belt.Option.flatMap(ts => ts##nodes)
         ->Belt.Option.getWithDefault([||])
         ->Belt.Array.mapWithIndex((index, tag) =>
             tag
             ->Belt.Option.map(tag =>
                 <Text
                   key={
                     tag##slug
                     ->Belt.Option.getWithDefault(string_of_int(index))
                   }>
                   <TextLink
                     style=styles##tag
                     href={
                       "/tags/"
                       ++ Utils.encodeURI(
                            tag##slug->Belt.Option.getWithDefault(""),
                          )
                       ++ "/"
                     }>
                     {"#"
                      ++ Utils.tagifyString(
                           tag##name->Belt.Option.getWithDefault(""),
                         )
                      |> ReasonReact.string}
                   </TextLink>
                   " "->ReasonReact.string
                 </Text>
               )
             ->Belt.Option.getWithDefault(ReasonReact.null)
           )
         ->ReasonReact.array}
      </SpacedView>
      <Author />
      <Spacer size=XL />
      <ViewportObserver>
        ...{state =>
          <PostRelatedPosts
            hasBeenVisible=state##hasBeenVisible
            postId=item##postId
          />
        }
      </ViewportObserver>
      <Spacer size=XL />
      <Comments
        postId=item##postId
        commentCounts=item##commentCount
        comments=item##comments
      />
    </View>;
  },
};
