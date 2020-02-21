open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "block":
        style([
          flexGrow(1.),
          flexShrink(1.),
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
let make = (~item: WPGraphQL.Fragments.PostDetailFragment.t, ()) => {
  let id = item##id;
  let rootCategory = item->Utils.rootCategory;
  let catHref = rootCategory->Utils.catHref;
  let href = item->Utils.postHref;
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
          <ViewLink href=catHref>
            <Text style=styles##categoryText>
              {rootCategory
               ->Option.flatMap(cat => cat##name)
               ->Option.getWithDefault("")
               ->String.uppercase
               ->React.string}
            </Text>
          </ViewLink>
          <Text style=styles##date>
            {({j|   ·   |j} ++ {item##dateGmt->Utils.frenchDate})
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
      <Spacer size=S />
      <Html content=item##content category=?rootCategory />
      <Spacer size=L />
      <View style=styles##tags>
        {item##tags
         ->Option.flatMap(ts => ts##nodes)
         ->Option.getWithDefault([||])
         ->Array.mapWithIndex((index, tag) =>
             tag
             ->Option.map(tag =>
                 <Text
                   key={
                     tag##slug->Option.getWithDefault(string_of_int(index))
                   }>
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
      </View>
      <Spacer size=XL />
      <Author />
      <Spacer size=L />
      <Comments
        postId=item##postId
        commentCounts=item##commentCount
        comments=item##comments
      />
    </SpacedView>
    <SpacedView vertical=None>
      <TextSubtitle> {j|Dans le même style|j}->React.string </TextSubtitle>
    </SpacedView>
    <PostList
      nodes={
        rootCategory
        ->Option.flatMap(category => category##posts)
        ->Option.flatMap(posts => posts##nodes)
        ->Option.getWithDefault([||])
        ->Array.keep(node =>
            node
            ->Option.map(node => node##id != item##id)
            ->Option.getWithDefault(false)
          )
        ->Array.slice(~offset=0, ~len=4)
      }
    />
  </View>;
};
