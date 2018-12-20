open BsReactNative;

let imageRatio = 240. /. 350.;
let radius = 3.;

let styles =
  StyleSheet.create(
    Style.{
      "wrapper": style([flex(1.), flexBasis(Pt(340.))]),
      "container":
        Dimensions.get(`window)##width <= 500 ?
          style([
            shadowColor(String("#333333")),
            shadowOffset(~height=4., ~width=0.),
            shadowOpacity(0.1),
            shadowRadius(20.),
          ]) :
          style([]),
      "row": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "image":
        style([borderTopLeftRadius(radius), borderTopRightRadius(radius)]),
      "text":
        style([
          borderBottomLeftRadius(radius),
          borderBottomRightRadius(radius),
          borderLeftWidth(StyleSheet.hairlineWidth),
          borderRightWidth(StyleSheet.hairlineWidth),
          borderBottomWidth(StyleSheet.hairlineWidth),
          borderColor(String("#EBEBEB")),
          backgroundColor(String("#FFF")),
        ]),
      "category":
        style([
          paddingTop(Pt(Spacer.space)),
          paddingHorizontal(Pt(Spacer.space)),
          flex(1.),
          fontSize(Float(10.)),
          color(String("#DE6D88")),
        ]),
      "actions":
        style([
          display(Flex),
          flexDirection(Row),
          fontSize(Float(10.)),
          color(String(ButtonLike.defaultColor)),
          paddingTop(Pt(Spacer.space)),
          paddingHorizontal(Pt(Spacer.space)),
        ]),
      "action":
        style([display(Flex), flexDirection(Row), alignItems(Center)]),
      "title":
        style([
          paddingTop(Pt(Spacer.space /. 2.)),
          paddingBottom(Pt(Spacer.space)),
          paddingHorizontal(Pt(Spacer.space)),
          fontSize(Float(22.)),
          fontWeight(`_300),
          lineHeight(28.),
          color(String("#1C1C1C")),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("PostPreviewFromGraphQLQuery");

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
    <SpacedView key=item##id style=styles##wrapper vertical=M horizontal=M>
      <TouchableScale
        style=styles##container activeScale=0.98 friction=5. tension=50.>
        <TextLink href>
          {item##featuredImage
           ->Belt.Option.flatMap(f => f##mediaDetails)
           ->Belt.Option.flatMap(m => m##sizes)
           ->Belt.Option.getWithDefault([||])
           ->Belt.Array.keepMap(x => x)
           ->Belt.Array.get(1)
           ->Belt.Option.flatMap(s => s##sourceUrl)
           ->Belt.Option.map(uri =>
               <ImageWithAspectRatio uri style=styles##image />
             )
           ->Belt.Option.getWithDefault(ReasonReact.null)}
        </TextLink>
        <View style=styles##text>
          <View style=styles##row>
            <TextLink style=styles##category href>
              {rootCategory##name
               ->Belt.Option.getWithDefault("")
               ->String.uppercase
               ->ReasonReact.string}
            </TextLink>
            <Text style=styles##actions>
              {switch (item##likeCount->Belt.Option.getWithDefault(0)) {
               | 0 => ReasonReact.null
               | v => (v->string_of_int ++ "  ")->ReasonReact.string
               }}
              <ButtonLike id=item##id />
              <Text> "    "->ReasonReact.string </Text>
              <TextLink style=styles##action href={href ++ "#comments"}>
                <SVGSpeechBubbleOutline
                  fill=ButtonLike.defaultColor
                  width=ButtonLike.defaultSize
                  height=ButtonLike.defaultSize
                />
                {switch (item##commentCount->Belt.Option.getWithDefault(0)) {
                 | 0 => ReasonReact.null
                 | v => ("  " ++ v->string_of_int)->ReasonReact.string
                 }}
              </TextLink>
            </Text>
          </View>
          <TextLink style=styles##title href>
            <span
              dangerouslySetInnerHTML={
                "__html": item##title->Belt.Option.getWithDefault(""),
              }
            />
          </TextLink>
        </View>
      </TouchableScale>
    </SpacedView>;
  },
};
