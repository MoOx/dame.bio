open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper": style([flex(1.), flexBasis(Pt(340.))]),
      "container":
        style([
          flex(1.),
          borderRadius(Consts.Radius.box),
          shadowColor(String("#333333")),
          shadowOffset(~height=2., ~width=0.),
          shadowOpacity(0.04),
          shadowRadius(16.),
        ]),
      "containerContent": style([flex(1.)]),
      "image":
        style([
          borderTopLeftRadius(Consts.Radius.box),
          borderTopRightRadius(Consts.Radius.box),
        ]),
      "text":
        style([
          flex(1.),
          borderBottomLeftRadius(Consts.Radius.box),
          borderBottomRightRadius(Consts.Radius.box),
          borderLeftWidth(0.5),
          borderRightWidth(0.5),
          borderBottomWidth(0.5),
          borderColor(String("#efefef")),
          backgroundColor(String(Consts.Colors.lightest)),
        ]),
      "categoryText":
        style([fontSize(Float(10.)), color(String(Consts.Colors.pink))]),
      "titleText":
        style([
          fontSize(Float(20.)),
          fontWeight(`_300),
          lineHeight(28.),
          color(String("#1C1C1C")),
        ]),
      "actionsWrapper":
        style([
          position(Absolute),
          top(Pt(0.)),
          left(Pt(0.)),
          right(Pt(0.)),
        ]),
      "actions":
        style([
          flexDirection(Row),
          right(Pt(0.)),
          alignSelf(FlexEnd),
          alignItems(Center),
          paddingTop(Pt(Spacer.space *. 3. /. 4.)),
          paddingRight(Pt(Spacer.space)),
        ]),
      "actionWrapper": style([flexDirection(Row)]),
      "action": style([display(Flex), flexDirection(Row)]),
      "actionText":
        style([
          fontSize(Float(10.)),
          color(String(ButtonLike.defaultColor)),
        ]),
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
      let rootCategory =
        item##categories
        ->Option.flatMap(categories => categories##nodes)
        ->Option.map(nodes => nodes->Array.keepMap(node => node))
        ->Option.flatMap(categoriesNodes => categoriesNodes[0]);

      let catHref =
        "/"
        ++ rootCategory
           ->Option.flatMap(cat => cat##slug)
           ->Option.getWithDefault("_")
           ->Utils.encodeURI
        ++ "/";
      let href =
        catHref ++ item##slug->Option.getWithDefault(item##id) ++ "/";
      let image =
        <ImageWithAspectRatio
          uri=?{
            item##featuredImage
            ->Option.flatMap(f => f##mediaDetails)
            ->Option.flatMap(m => m##sizes)
            ->Option.getWithDefault([||])
            ->Array.keep(size =>
                size
                ->Option.map(size =>
                    size##name->Option.getWithDefault("") === "medium"
                  )
                ->Option.getWithDefault(false)
              )
            ->Array.get(0)
            ->Option.flatMap(s => s->Option.map(s => s##sourceUrl))
            ->Option.getWithDefault(None)
          }
          style=styles##image
          ratio=imageRatio
        />;
      let categoryName =
        rootCategory
        ->Option.flatMap(cat => cat##name)
        ->Option.getWithDefault("")
        ->String.uppercase
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
                 style([
                   position(Absolute),
                   bottom(Pt(-10.)),
                   right(Pt(-15.)),
                   width(Pt(723. /. 2.)),
                   height(Pt(495. /. 2.)),
                 ])
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
                  width=ButtonLike.defaultSize
                  height=ButtonLike.defaultSize
                />
                <Text style=styles##actionText> comments </Text>
              </ViewLink>
            </View>
          </SpacedView>
      </SpacedView>;
    },
  });
