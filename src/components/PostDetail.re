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
      "metaRowLeft": style([flexDirection(Row), alignItems(Baseline)]),
      "date":
        style([fontSize(Float(12.)), color(String(Consts.Colors.grey))]),
      "title":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(32.)),
          lineHeight(32. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
      "categoryText":
        style([fontSize(Float(14.)), color(String("#DE6D88"))]),
      "actions":
        style([
          flexDirection(Row),
          alignSelf(FlexEnd),
          alignItems(Center),
        ]),
      "action": style([flexDirection(Row)]),
      "actionText":
        style([
          fontSize(Float(10.)),
          color(String(ButtonLike.defaultColor)),
        ]),
      "link": style([padding(Pt(10.))]),
      "tags":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "tagText":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          color(String("#006579")),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("PostDetail");

let make = (~item, _) => {
  ...component,
  render: _self => {
    let id = item##id;
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
    let likes = {
      switch (item##likeCount->Belt.Option.getWithDefault(0)) {
      | 0 => ReasonReact.null
      | v => (v->string_of_int ++ "  ")->ReasonReact.string
      };
    };
    let comments = {
      switch (item##commentCount->Belt.Option.getWithDefault(0)) {
      | 0 => ReasonReact.null
      | v => ("  " ++ v->string_of_int)->ReasonReact.string
      };
    };
    <ViewWeb style=styles##block accessibilityRole="article">
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
.dbPost h2 {
  font-weight: 800;
  font-size: 20px;
  margin: 40px 0 20px;
}

.dbPost .ingredients dt::before,
.dbPost h2::before {
  content: "☆ ";
}

.dbPost dd { margin: 0 }

.wp-block-image {
  margin: 8% auto;
  max-width: 90%;
}

.wp-block-image figcaption {
  color: #555d66;
  font-size: 14px;
  margin-top: 10px;
  text-align: center;
}

.dbtmp-element-protector-wrapper {
  position: relative;
  display: block;
  margin: 0;
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
      <TextWeb style=styles##title accessibilityRole="heading">
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Belt.Option.getWithDefault(""),
          }
        />
      </TextWeb>
      <View style=styles##metaRow>
        <View style=styles##metaRowLeft>
          <ViewLink
            href={
              "/"
              ++ Utils.encodeURI(
                   rootCategory##slug->Belt.Option.getWithDefault("_"),
                 )
              ++ "/"
            }>
            <Text style=styles##categoryText>
              {String.uppercase(
                 rootCategory##name->Belt.Option.getWithDefault(""),
               )
               ->ReasonReact.string}
            </Text>
          </ViewLink>
          <Text style=styles##date>
            {(
               {j|   ·   |j}
               ++ item##dateGmt
                  ->Belt.Option.mapWithDefault(Js.Date.make(), d =>
                      Js.Date.fromString(d |> Js.String.replace(" ", "T"))
                    )
                  ->Js.Date.toLocaleDateString
             )
             ->ReasonReact.string}
          </Text>
        </View>
        <View style=styles##actions pointerEvents=`boxNone>
          <View style=styles##action>
            <Text style=styles##actionText> likes </Text>
            <ButtonLike id />
          </View>
          <Text> "    "->ReasonReact.string </Text>
          <ViewLink style=styles##action href={href ++ "#comments"}>
            <SVGSpeechBubbleOutline
              fill=ButtonLike.defaultColor
              width=ButtonLike.defaultSize
              height=ButtonLike.defaultSize
            />
            <Text style=styles##actionText> comments </Text>
          </ViewLink>
        </View>
      </View>
      <Spacer size=L />
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
                   [%re "/<p style=\"text-align:center\">☆<\\/p>/g"],
                   ""
                   ++ "<span style=\"display: block; text-align: center; margin: 40px;\">"
                   ++ "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />"
                   ++ "</span>",
                 )
              /* custom behavior decided for us hr => a png */
              |> Js.String.replaceByRe(
                   [%re "/<hr ?(class=\"wp-block-separator\")? ?\\/?>/g"],
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
                   [%re "/<p style=\"text-align:center\">---<\\/p>/g"],
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
                     href={
                       "/tag/"
                       ++ Utils.encodeURI(
                            tag##slug->Belt.Option.getWithDefault(""),
                          )
                       ++ "/"
                     }>
                     <Text style=styles##tagText>
                       {"#"
                        ++ Utils.tagifyString(
                             tag##name->Belt.Option.getWithDefault(""),
                           )
                        |> ReasonReact.string}
                     </Text>
                   </TextLink>
                   " "->ReasonReact.string
                 </Text>
               )
             ->Belt.Option.getWithDefault(ReasonReact.null)
           )
         ->ReasonReact.array}
      </SpacedView>
      <Spacer size=L />
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
    </ViewWeb>;
  },
};
