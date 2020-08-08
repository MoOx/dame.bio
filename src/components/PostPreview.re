open Belt;
open ReactNative;

let imageRatio = 240. /. 350.;

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
          ~paddingTop=(Spacer.space *. 3. /. 4.)->dp,
          ~paddingRight=Spacer.space->dp,
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

let component = ReasonReact.reducerComponent("PostPreview");

[@react.component]
let make = (~item, ~withWatercolorBottomRightCorner=false, ()) =>
  ReactCompat.useRecordApi({
    ...component,
    initialState: () => {focusTimeout: ref(None), focus: false},
    reducer: (action, state) =>
      switch (action) {
      | WillFocus(cb) =>
        clearOptionalTimeout(state.focusTimeout);
        ReasonReact.SideEffects(
          _ => state.focusTimeout := Some(Js.Global.setTimeout(cb, timing)),
        );
      | Focus =>
        clearOptionalTimeout(state.focusTimeout);
        ReasonReact.Update({...state, focus: true});
      | WillBlur(cb) =>
        clearOptionalTimeout(state.focusTimeout);
        ReasonReact.SideEffects(
          _ => state.focusTimeout := Some(Js.Global.setTimeout(cb, timing)),
        );
      | Blur =>
        clearOptionalTimeout(state.focusTimeout);
        ReasonReact.Update({...state, focus: false});
      },
    render: ({send}) => {
      let id = item##id;
      let rootCategory = item->Utils.rootCategory;
      let href = item->Utils.postHref;
      let uris =
        item##featuredImage
        ->Option.flatMap(f => f##mediaDetails)
        ->Option.flatMap(m => m##sizes)
        ->Option.map(sizes => sizes->Array.keepMap(o => o))
        // ->Option.map(sizes =>
        //     sizes->Array.keep(size =>
        //       Js.Array.includes(
        //         size##name->Option.getWithDefault(""),
        //         Consts.imageSizes,
        //       )
        //     )
        //   )
        ->Option.getWithDefault([||]);
      let image =
        <ImageWithAspectRatio uris style=styles##image ratio=imageRatio />;
      let categoryName =
        rootCategory
        ->Option.flatMap(cat => cat##name)
        ->Option.getWithDefault("")
        ->Js.String.toUpperCase
        ->React.string;
      let title = item##title->Option.getWithDefault("");
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
        <ViewLink
          href
          style=styles##container
          onMouseEnter={() => send(WillFocus(() => send(Focus)))}
          onMouseLeave={() => send(WillBlur(() => send(Blur)))}>
          <View style=styles##containerContent>
            image
            <SpacedView vertical=M horizontal=M style=styles##text>
              <Text style=styles##categoryText> categoryName </Text>
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
          /*
                 // onMouseEnter={() =>
                 //   send(
                 //     WillFocus(() => Webapi.requestAnimationFrame(_ => send(Focus))),
                 //   )
                 // }
                 // onMouseLeave={() =>
                 //   send(
                 //     WillBlur(() => Webapi.requestAnimationFrame(_ => send(Blur))),
                 //   )
                 // }
           */

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
                  width={ButtonLike.defaultSize->Js.Float.toString}
                  height={ButtonLike.defaultSize->Js.Float.toString}
                />
                <Text style=styles##actionText> comments </Text>
              </ViewLink>
            </View>
          </SpacedView>
      </SpacedView>;
    },
  });
