open Helpers;

open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          flex(1.),
          /* flexBasis(Pt(350.)), */
          borderWidth(1.),
          borderColor(String("#F0F0EF")),
          marginRight(Pt(40.)),
          marginBottom(Pt(40.)),
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
          fontSize(Float(32.)),
          fontWeight(`_300),
          lineHeight(32. *. 1.5),
          marginBottom(Pt(10.)),
          color(String("#006579")),
        ]),
      "link": style([padding(Pt(10.))]),
      "subtitle":
        style([
          fontSize(Float(28.)),
          lineHeight(28. *. 1.5),
          marginBottom(Pt(10.)),
          color(String("#1C1C1C")),
        ]),
    },
  );

let findRootCategory = (item: Structures.post): Structures.term =>
  List.find(
    (term: Structures.term) => !term.hasParent,
    item.terms.categories,
  );

let component = ReasonReact.statelessComponent("PostDetail");

let make = (~item: Structures.post, _) => {
  ...component,
  render: _self => {
    let rootCategory = findRootCategory(item);
    let href =
      "/"
      ++ String.lowercase(rootCategory.slug)
      ++ "/"
      ++ String.lowercase(item.slug)
      ++ "/";
    <View key={string_of_int(item.id)} style=styles##block>
      <View style=styles##text>
        <Text style=styles##title>
          <span dangerouslySetInnerHTML={"__html": item.title} />
        </Text>
        <View style=styles##row>
          <TextLink
            style=styles##category
            href={"/tag/" ++ Utils.encodeURI(rootCategory.slug)}>
            {String.uppercase(rootCategory.name) |> text}
          </TextLink>
          <Text style=styles##actions>
            <TextLink style=styles##action href="#like">
              <SVGFavorite fill="#ddd" width=12. height=12. />
              {
                (
                  if (item.likes != 0) {
                    " " ++ (item.likes |> string_of_int);
                  } else {
                    "";
                  }
                )
                |> text
              }
            </TextLink>
            <Text style=styles##action> {" | " |> text} </Text>
            <TextLink style=styles##action href={href ++ "#comments"}>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
              {
                switch (item.comments) {
                | None => "" |> text
                | Some(comments) =>
                  " " ++ (List.length(comments) |> string_of_int) |> text
                }
              }
            </TextLink>
          </Text>
        </View>
        <div
          className="dbPost"
          dangerouslySetInnerHTML={
            "__html":
              Js.String.replaceByRe(
                [%re "/=\"\\/wp-content/g"],
                "=\"https://dame.bio/wp-content",
                Js.String.replaceByRe(
                  [%re "/\\u2b50\\ufe0e(<br \\/>?)/g"],
                  ""
                  ++ "<span style=\"display: block; text-align: center; margin: 40px;\">"
                  ++ "<span style=\"display: inline-block;background: url(/images/line_flower.png) no-repeat; height: 14px; width: 68px;\"></span>"
                  /* ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-left.png) no-repeat; height: 21px; width: 17px;\"></span>"
                     ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-tile.png) repeat-x; height: 21px; width: 80%;\"></span>"
                     ++ "<span style=\"display: inline-block;background: url(/images/line-arrow-right.png) no-repeat; height: 21px; width: 66px;\"></span>" */
                  ++ "</span>",
                  item.contentHTML,
                ),
              ),
          }
        />
        <Spacer />
        <View>
          <Text style=styles##subtitle> {"Commentaires" |> text} </Text>
        </View>
        <Comments comments=item.comments />
      </View>
    </View>;
  },
};
