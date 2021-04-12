open Belt;
open ReactNative;

let imageWidth = 512.;
let imageHeight = 384.;
let imageRatio = imageHeight /. imageWidth;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper":
        viewStyle(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~flexBasis=340.->dp,
          ~overflow=`hidden,
          (),
        ),
      "container":
        viewStyle(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~borderRadius=Consts.Radius.box,
          ~shadowColor="#333333",
          ~shadowOffset=offset(~height=2., ~width=0.),
          ~shadowOpacity=0.04,
          ~shadowRadius=16.,
          (),
        ),
      "containerContent": viewStyle(~flexGrow=1., ~flexShrink=1., ()),
      "image":
        viewStyle(
          ~borderTopLeftRadius=Consts.Radius.box,
          ~borderTopRightRadius=Consts.Radius.box,
          ~backgroundColor=Consts.Colors.lightGrey,
          (),
        ),
      "text":
        viewStyle(
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~borderBottomLeftRadius=Consts.Radius.box,
          ~borderBottomRightRadius=Consts.Radius.box,
          ~borderLeftWidth=0.5,
          ~borderRightWidth=0.5,
          ~borderBottomWidth=0.5,
          ~borderColor="#efefef",
          ~backgroundColor=Consts.Colors.lightest,
          (),
        ),
      "categoryText": textStyle(~fontSize=10., ~color=Consts.Colors.pink, ()),
      "dateText": textStyle(~fontSize=10., ~color=Consts.Colors.grey, ()),
      "titleText":
        textStyle(
          ~fontSize=20.,
          ~fontWeight=`_300,
          ~lineHeight=28.,
          ~color="#1C1C1C",
          (),
        ),
      "actionsWrapper":
        viewStyle(
          ~position=`absolute,
          ~top=0.->dp,
          ~left=0.->dp,
          ~right=0.->dp,
          (),
        ),
      "actions":
        viewStyle(
          ~flexDirection=`row,
          ~right=0.->dp,
          ~alignSelf=`flexEnd,
          ~alignItems=`center,
          (),
        ),
      "actionWrapper": viewStyle(~flexDirection=`row, ()),
      "action": viewStyle(~display=`flex, ~flexDirection=`row, ()),
      "actionText":
        textStyle(~fontSize=10., ~color=ButtonLike.defaultColor, ()),
    })
  );

type action =
  | WillFocus(unit => unit)
  | Focus
  | WillBlur(unit => unit)
  | Blur;

type state = {
  focus: bool,
  focusTimeout: ref(option(Js.Global.timeoutId)),
};

let timing = 150;
let clearOptionalTimeout = optionalTimeoutRef =>
  (optionalTimeoutRef^)->Option.map(Js.Global.clearTimeout)->ignore;

[@react.component]
let make =
    (
      ~item: WPGraphQL.PostPreviewFragment.t,
      ~withWatercolorBottomRightCorner=false,
      (),
    ) => {
  let id = item.id;
  let rootCategory =
    item.categories
    ->Option.flatMap(categories => categories.nodes)
    ->Option.map(nodes => nodes->Array.keepMap(node => node))
    ->Option.flatMap(categoriesNodes => categoriesNodes[0]);
  let href =
    "/"
    ++ rootCategory
       ->Option.flatMap(cat => cat.slug)
       ->Option.getWithDefault("_")
       ->Utils.encodeURI
    ++ "/"
    ++ item.slug->Option.getWithDefault(item.id);
  let uris =
    item.featuredImage
    ->Option.flatMap(f => f.mediaDetails)
    ->Option.flatMap(m => m.sizes)
    ->Option.map(sizes => sizes->Array.keepMap(o => o))
    ->Option.getWithDefault([||])
    ->Array.keep(img =>
        img.width->Option.getWithDefault("0")->Js.Float.fromString < 1024.
      );
  let featuredImageUri =
    uris->Js.Array2.sortInPlaceWith((a, b) => {
      let wa = a.width->Option.getWithDefault("0")->Js.Float.fromString;
      let wb = b.width->Option.getWithDefault("0")->Js.Float.fromString;
      wa < wb ? 1 : wa > wb ? (-1) : 0;
    })[0]
    ->Option.flatMap(i => i.sourceUrl);
  let categoryName =
    rootCategory
    ->Option.flatMap(cat => cat.name)
    ->Option.getWithDefault("")
    ->Js.String.toUpperCase
    ->React.string;
  let title = item.title->Option.getWithDefault("");
  let likes =
    switch (item.likeCount->Option.getWithDefault(0)) {
    | 0 => React.null
    | v => (v->string_of_int ++ "  ")->React.string
    };
  let comments =
    switch (item.commentCount->Option.getWithDefault(0)) {
    | 0 => React.null
    | v => ("  " ++ v->string_of_int)->React.string
    };
  <SpacedView key=id style=styles##wrapper vertical=M horizontal=M>
    {withWatercolorBottomRightCorner
       ? <ImageFromUri
           resizeMode=`contain
           uri="/images/watercolor-bottom-right.png"
           style=Style.(
             viewStyle(
               ~position=`absolute,
               ~bottom=(-10.)->dp,
               ~right=(-15.)->dp,
               ~width=(723. /. 2.)->dp,
               ~height=(495. /. 2.)->dp,
               (),
             )
           )
         />
       : React.null}
    <ViewLink href style=styles##container>
      <View style=styles##containerContent>
        <PlaceholderWithAspectRatio ratio=imageRatio style={styles##image}>
          {featuredImageUri
           ->Option.map(src =>
               <Next.Image
                 className="PostPreview-img"
                 src
                 width=imageWidth
                 height=imageHeight
                 layout=`responsive
                 objectFit=`cover
               />
             )
           ->Option.getWithDefault(React.null)}
        </PlaceholderWithAspectRatio>
        <SpacedView vertical=S horizontal=M style=styles##text>
          <Text>
            <Text style=styles##categoryText> categoryName </Text>
            <Text style=styles##dateText>
              <Text> {j|  ·  |j}->React.string </Text>
              {item.dateGmt->Utils.frenchDate->React.string}
            </Text>
          </Text>
          <Spacer size=XS />
          <Text style=styles##titleText>
            <span dangerouslySetInnerHTML={"__html": title} />
          </Text>
          <Spacer size=XS />
        </SpacedView>
      </View>
    </ViewLink>
    <SpacedView
      vertical=M
      horizontal=M
      style=styles##actionsWrapper
      pointerEvents=`boxNone>
      <PlaceholderWithAspectRatio ratio=imageRatio />
      <SpacedView
        vertical=S horizontal=M style=styles##actions pointerEvents=`boxNone>
        <View style=styles##action>
          <Text style=styles##actionText> likes </Text>
          <ButtonLike id />
        </View>
        <Text> "    "->React.string </Text>
        <ViewLink style=styles##action href={href ++ "#comments"}>
          <SVGSpeechBubbleOutline
            fill=ButtonLike.defaultColor
            width={ButtonLike.defaultSize->Js.Float.toString}
            height={ButtonLike.defaultSize->Js.Float.toString}
          />
          <Text style=styles##actionText> comments </Text>
        </ViewLink>
      </SpacedView>
    </SpacedView>
  </SpacedView>;
};
