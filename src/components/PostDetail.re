open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "block":
        style([
          flex(1.),
          borderColor(String("#F0F0EF")),
          backgroundColor(String("#fff")),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "metaRowLeft": style([flexDirection(Row), alignItems(Baseline)]),
      "date":
        style([fontSize(Float(12.)), color(String(Consts.Colors.grey))]),
      "categoryText":
        style([fontSize(Float(14.)), color(String(Consts.Colors.pink))]),
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
    })
  );

[@react.component]
let make = (~item, ()) => {
  let id = item##id;
  let rootCategory =
    T.getMainCategory(
      item##categories
      ->Option.flatMap(cs => cs##nodes)
      ->Option.getWithDefault([||]),
    );
  let href =
    "/"
    ++ rootCategory##slug->Option.getWithDefault("_")
    ++ "/"
    ++ item##slug->Option.getWithDefault(item##id)
    ++ "/";
  let likes =
    switch (item##likeCount->Option.getWithDefault(0)) {
    | 0 => React.null
    | v => (v->string_of_int ++ "  ")->React.string
    };
  let comments =
    switch (item##commentCount->Option.getWithDefault(0)) {
    | 0 => React.null
    | v => ("  " ++ v->string_of_int)->React.string
    };
  <View style=styles##block /*accessibilityRole=`webAriaArticle*/>
    <SpacedView>
      <Heading>
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Option.getWithDefault(""),
          }
        />
      </Heading>
      <Spacer size=S />
      <View style=styles##metaRow>
        <View style=styles##metaRowLeft>
          <ViewLink
            href={
              "/"
              ++ Utils.encodeURI(
                   rootCategory##slug->Option.getWithDefault("_"),
                 )
              ++ "/"
            }>
            <Text style=styles##categoryText>
              {rootCategory##name
               ->Option.getWithDefault("")
               ->String.uppercase
               ->React.string}
            </Text>
          </ViewLink>
          <Text style=styles##date>
            {(
               {j|   ·   |j}
               ++ item##dateGmt
                  ->Option.mapWithDefault(Js.Date.make(), d =>
                      Js.Date.fromString(d |> Js.String.replace(" ", "T"))
                    )
                  ->Js.Date.toLocaleDateString
             )
             ->React.string}
          </Text>
        </View>
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
      </View>
    </SpacedView>
    <Html content=item##content category=rootCategory />
    <SpacedView vertical=L style=styles##tags>
      {item##tags
       ->Option.flatMap(ts => ts##nodes)
       ->Option.getWithDefault([||])
       ->Array.mapWithIndex((index, tag) =>
           tag
           ->Option.map(tag =>
               <Text
                 key={tag##slug->Option.getWithDefault(string_of_int(index))}>
                 <TextLink
                   href={
                     "/tag/"
                     ++ Utils.encodeURI(
                          tag##slug->Option.getWithDefault(""),
                        )
                     ++ "/"
                   }>
                   <Text style=styles##tagText>
                     {"#"
                      ++ Utils.tagifyString(
                           tag##name->Option.getWithDefault(""),
                         )
                      |> React.string}
                   </Text>
                 </TextLink>
                 " "->React.string
               </Text>
             )
           ->Option.getWithDefault(React.null)
         )
       ->React.array}
    </SpacedView>
    <Spacer />
    <SpacedView>
      <Author />
      <Spacer size=L />
      <Comments
        postId=item##postId
        commentCounts=item##commentCount
        comments=item##comments
      />
    </SpacedView>
    <ViewportObserver>
      ...{state =>
        <PostRelatedPosts
          hasBeenVisible=state##hasBeenVisible
          postId=item##postId
        />
      }
    </ViewportObserver>
  </View>;
};
