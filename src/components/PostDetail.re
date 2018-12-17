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
      <BsReactHelmet>
        <style>
          {j|
.dbPost {
  font-size: 16px;
  line-height: 29px;
  color: #49443A;
}
.dbPost a {
  color: #3ba013;
}
.dbPost strong {
  font-weight: 800;
}
.dbPost img {
  max-width: 100%;
}

.dbPost .ingredients dt,
.dbPost .tips-title {
  font-weight: 800;
  font-size: 18px;
}
.dbPost dd {
  margin: 0 0 0 20px;
}
.dbPost dd::before {
  content: "· "
}

.wp-block-image {
  margin: 8% auto;
  max-width: 90%;
}

.wp-block-image figcaption {
  color: #555d66;
  font-size: 14px;
  margin-bottom: 10px;
  margin-top: 10px;
  text-align: center;
}

.dbtmp-element-protector-wrapper {
  margin: 0;
  display: block;
  position: relative;
  background: #eee;
}
.dbtmp-element-protector-wrapper img {display: block;}
.dbtmp-element-protector-overlay {position:absolute;top:0;left:0;right:0;bottom:0;}

/* keep wordpress html default rendering */
.dbComment { white-space: normal }
.dbComment p { margin: 0; }
.dbComment a { color: #49443A; }
|j}
          ->ReasonReact.string
        </style>
      </BsReactHelmet>
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
      <SpacedView>
        <div
          className="dbPost"
          dangerouslySetInnerHTML={
            "__html":
              item##content->Belt.Option.getWithDefault("")
              /* make images url absolute */
              |> Js.String.replaceByRe(
                   [%re "/=\"\\/wp-content/g"],
                   "=\"https://dame.bio/wp-content",
                 )
              /* custom behavior decided for us "white star unicode" => a png */
              |> Js.String.replaceByRe(
                   [%re "/<p style=\"text-align: center;\">⭐︎<\\/p>/g"],
                   ""
                   ++ "<span style=\"display: block; text-align: center; margin: 40px;\">"
                   ++ "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />"
                   ++ "</span>",
                 )
              /* custom behavior decided for us hr => a png */
              |> Js.String.replaceByRe(
                   [%re "/<hr ?(class=\"wp-block-separator\")? ?\/?>/g"],
                   ""
                   ++ "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 60px auto; width: 80%;\">"
                   ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
                   ++ (
                     switch (
                       rootCategory##slug->Belt.Option.getWithDefault("")
                     ) {
                     | "alimentation" => "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />"
                     | "permaculture" => "<img src=\"/images/separator-feather.png\" style=\"margin: 0 10px; width: 36.5px; height: 11.5px;\" alt=\"\" />"
                     | _ => "<img src=\"/images/separator-hearts.png\" style=\"margin: 0 10px; width: 48px; height: 15px;\" alt=\"\" />"
                     }
                   )
                   ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
                   ++ "</span>",
                 )
              /* custom behavior decided for us --- => a png */
              |> Js.String.replaceByRe(
                   [%re "/\\n\\n---\\n\\n/g"],
                   ""
                   ++ "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 40px auto; width: 80%;\">"
                   ++ "<img src=\"/images/separator-long-head.png\" style=\"width: 14.5px; height: 7.5px; margin: 1px 0 0 0;\" alt=\"\" />"
                   ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
                   ++ "<img src=\"/images/separator-long-tail.png\" style=\"width: 64px; height: 19.5px;\" alt=\"\" />"
                   ++ "</span>",
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
      <Comments
        postId=item##postId
        commentCounts=item##commentCount
        comments=item##comments
      />
      <Spacer size=XL />
      <ViewportObserver>
        ...{state =>
          <PostRelatedPosts
            hasBeenVisible=state##hasBeenVisible
            postId=item##postId
          />
        }
      </ViewportObserver>
    </View>;
  },
};
