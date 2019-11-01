open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "block":
        style(
          ~position=`relative,
          ~flex=1.,
          ~backgroundColor=Consts.Colors.lightGrey,
          (),
        ),
      "image": style(~position=`relative, ~flex=1., ()),
      "overlay":
        style(
          ~position=`absolute,
          ~top=0.->dp,
          ~bottom=0.->dp,
          ~left=0.->dp,
          ~right=0.->dp,
          ~backgroundColor="rgba(0,0,0,0.3)",
          ~justifyContent=`center,
          ~alignItems=`center,
          ~flexDirection=`row,
          (),
        ),
      "overlayText":
        style(
          ~alignItems=`center,
          ~fontSize=16.,
          ~lineHeight=16.,
          ~fontWeight=`_600,
          ~color="#fff",
          (),
        ),
    })
  );

type action =
  | Focus
  | Blur;

type state = {focus: bool};

let component = ReasonReact.reducerComponent("InstagramPost");

[@react.component]
let make = (~item, ~size, ()) =>
  ReactCompat.useRecordApi({
    ...component,
    initialState: () => {focus: false},
    reducer: (action, _) =>
      switch (action) {
      | Focus => ReasonReact.Update({focus: true})
      | Blur => ReasonReact.Update({focus: false})
      },
    render: ({state, send}) => {
      let uri = item##images##standard_resolution##url;
      <ViewLink
        href=item##link
        style=Style.(
          array([|
            styles##block,
            style(~width=size->dp, ~height=size->dp, ()),
          |])
        )
        onMouseEnter={() => send(Focus)}
        onMouseLeave={() => send(Blur)}>
        <ImageFromUri style=styles##image uri />
        {state.focus
           ? <View style=styles##overlay>
               <SVGFavorite fill="#fff" width=19. height=19. />
               <Text style=styles##overlayText>
                 " "->React.string
                 {item##likes##count->string_of_int->React.string}
                 "      "->React.string
               </Text>
               <SVGSpeechBubbleRight fill="#fff" width=19. height=19. />
               <Text style=styles##overlayText>
                 " "->React.string
                 {item##comments##count->string_of_int->React.string}
               </Text>
             </View>
           : React.null}
      </ViewLink>;
    },
  });
