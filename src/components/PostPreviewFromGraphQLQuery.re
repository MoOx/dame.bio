open Helpers;

open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "unused": style([]),
      "block":
        style([
          flex(1.),
          flexBasis(Pt(340.)),
          borderWidth(0.75),
          borderColor(String("#EBEBEB")),
          backgroundColor(String("#FFF")),
        ]),
      "row": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "text": style([padding(Pt(20.))]),
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
        {
          item##featuredImage
          ->Belt.Option.flatMap(f => f##mediaDetails)
          ->Belt.Option.flatMap(m => m##sizes)
          ->Belt.Option.getWithDefault([||])
          ->Belt.Array.keepMap(x => x)
          ->Belt.Array.get(1)
          ->Belt.Option.flatMap(s => s##sourceUrl)
          ->Belt.Option.map(uri => <ImageWithAspectRatio uri />)
          ->Belt.Option.getWithDefault(nothing)
        }
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
            {
              rootCategory##name
              ->Belt.Option.getWithDefault("")
              ->String.uppercase
              ->text
            }
          </TextLink>
          <Text style=styles##actions>
            <TextLink style=styles##action href="#like">
              <SVGFavorite fill="#ddd" width=12. height=12. />
            </TextLink>
            /* {
                 (item##likes != 0 ? " " ++ (item##likes |> string_of_int) : "")
                 |> text
               } */
            <Text style=styles##action> {" | " |> text} </Text>
            <TextLink style=styles##action href={href ++ "#comments"}>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
              {
                switch (item##commentCount->Belt.Option.getWithDefault(0)) {
                | 0 => nothing
                | v => (" " ++ v->string_of_int)->text
                }
              }
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
