open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;
let radius = 3.;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper": style([flex(1.), flexBasis(Pt(340.))]),
      "container":
        Dimensions.get(`window)##width <= 500
          ? style([
              flex(1.),
              shadowColor(String("#333333")),
              shadowOffset(~height=4., ~width=0.),
              shadowOpacity(0.1),
              shadowRadius(20.),
            ])
          : style([
              flex(1.),
              shadowColor(String("#333333")),
              shadowOffset(~height=4., ~width=0.),
              shadowOpacity(0.05),
              shadowRadius(20.),
            ]),
      "containerContent":
        style([
          flex(1.),
          /* shadow to help differentiate the top left flowers */
          shadowColor(String("#fff")),
          shadowOffset(~height=-1., ~width=-1.),
          shadowOpacity(0.5),
          shadowRadius(0.),
        ]),
      "image":
        style([borderTopLeftRadius(radius), borderTopRightRadius(radius)]),
      "text":
        style([
          flex(1.),
          borderBottomLeftRadius(radius),
          borderBottomRightRadius(radius),
          borderLeftWidth(StyleSheet.hairlineWidth),
          borderRightWidth(StyleSheet.hairlineWidth),
          borderBottomWidth(StyleSheet.hairlineWidth),
          borderColor(String(Consts.Colors.lightGrey)),
          backgroundColor(String(Consts.Colors.lightest)),
        ]),
      "categoryText":
        style([fontSize(Float(10.)), color(String("#DE6D88"))]),
      "titleText":
        style([
          fontSize(Float(22.)),
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

let component = ReasonReact.reducerComponent("PostPreviewFromGraphQLQuery");

[@react.component]
let make = (~item, ~withFlowers=false, ~withWatercolorCorner=false, ()) =>
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
      let image =
        item##featuredImage
        ->Option.flatMap(f => f##mediaDetails)
        ->Option.flatMap(m => m##sizes)
        ->Option.getWithDefault([||])
        ->Array.keepMap(x => x)
        ->Array.get(1)
        ->Option.flatMap(s => s##sourceUrl)
        ->Option.map(uri =>
            <ImageWithAspectRatio uri style=styles##image ratio=imageRatio />
          )
        ->Option.getWithDefault(React.null);
      let category =
        rootCategory##name
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
        {withFlowers
           ? <ImageFromUri
               resizeMode=`contain
               uri="/images/preview-corner-top-left.png"
               style=Style.(
                 style([
                   position(Absolute),
                   top(Pt(-6.)),
                   left(Pt(-10.)),
                   width(Pt(290. /. 2.)),
                   height(Pt(491. /. 2.)),
                 ])
               )
             />
           : React.null}
        {withWatercolorCorner
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
              <Text style=styles##categoryText> category </Text>
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
