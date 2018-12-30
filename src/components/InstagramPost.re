open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          position(Relative),
          flex(1.),
          width(Pt(293.)),
          height(Pt(293.)),
        ]),
      "overlay":
        style([
          position(Absolute),
          top(Pt(0.)),
          bottom(Pt(0.)),
          left(Pt(0.)),
          right(Pt(0.)),
          backgroundColor(String("rgba(0,0,0,0.3)")),
          justifyContent(Center),
          alignItems(Center),
          flexDirection(Row),
        ]),
      "overlayText":
        style([
          alignItems(Center),
          fontSize(Float(16.)),
          lineHeight(16.),
          fontWeight(`Bold),
          color(String("#fff")),
        ]),
    },
  );

type action =
  | Focus
  | Blur;

type state = {focus: bool};

let component = ReasonReact.reducerComponent("InstagramPost");

let make = (~item, _children) => {
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
      style=styles##block
      onMouseEnter={() => send(Focus)}
      onMouseLeave={() => send(Blur)}>
      <Image
        style=styles##block
        source={`URI(Image.(imageURISource(~uri, ())))}
      />
      {state.focus ?
         <View style=styles##overlay>
           <SVGFavorite fill="#fff" width=19. height=19. />
           <Text style=styles##overlayText>
             " "->ReasonReact.string
             {string_of_int(item##likes##count)->ReasonReact.string}
             "      "->ReasonReact.string
           </Text>
           <SVGSpeechBubbleRight fill="#fff" width=19. height=19. />
           <Text style=styles##overlayText>
             " "->ReasonReact.string
             {string_of_int(item##comments##count)->ReasonReact.string}
           </Text>
         </View> :
         ReasonReact.null}
    </ViewLink>;
  },
};
