open BsReactNative;

let imageRatio = 240. /. 350.;
let radius = 3.;

let styles =
  StyleSheet.create(
    Style.{
      "block": style([flex(1.), flexBasis(Pt(340.))]),
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
          padding(Pt(20.)),
        ]),
      "category":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(10.)),
          color(String("#DE6D88")),
        ]),
      "actions":
        style([
          display(Flex),
          flexDirection(Row),
          marginBottom(Pt(10.)),
          fontSize(Float(10.)),
          color(String("#bbb")),
        ]),
      "action":
        style([
          display(Flex),
          flexDirection(Row),
          marginHorizontal(Pt(4.)),
        ]),
      "title":
        style([
          fontSize(Float(22.)),
          fontWeight(`_300),
          lineHeight(28.),
          color(String("#1C1C1C")),
        ]),
      "link": style([padding(Pt(10.))]),
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
    <SpacedView key=item##id style=styles##block vertical=M horizontal=M>
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
          <TextLink
            style=styles##category
            href={
              "/"
              ++ rootCategory##slug->Belt.Option.getWithDefault("_")
              ++ "/"
            }>
            {rootCategory##name
             ->Belt.Option.getWithDefault("")
             ->String.uppercase
             ->ReasonReact.string}
          </TextLink>
          <Text style=styles##actions>
            <ButtonLike id=item##id />
            {switch (item##likeCount->Belt.Option.getWithDefault(0)) {
             | 0 => ReasonReact.null
             | v => ("  " ++ v->string_of_int)->ReasonReact.string
             }}
            <Text style=styles##action> " | "->ReasonReact.string </Text>
            <TextLink style=styles##action href={href ++ "#comments"}>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
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
    </SpacedView>;
  },
};
