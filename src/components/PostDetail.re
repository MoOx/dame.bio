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
          /* borderWidth(1.),
             borderRadius(6.), */
          borderColor(String("#F0F0EF")),
          marginRight(Pt(40.)),
          marginBottom(Pt(40.)),
          backgroundColor(String("#fff")),
          paddingHorizontal(Pt(20.)),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "tags":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "tag":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          color(String("#006579")),
        ]),
      "category": style([fontSize(Float(14.)), color(String("#DE6D88"))]),
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
          marginBottom(Pt(10.)),
          fontSize(Float(32.)),
          lineHeight(32. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
      "link": style([padding(Pt(10.))]),
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
    <View style=styles##block>
      <PostRelatedPosts postId={item.id} />
      <Text style=styles##title>
        <span dangerouslySetInnerHTML={"__html": item.title} />
      </Text>
      <View style=styles##metaRow>
        <TextLink
          style=styles##category
          href={"/" ++ Utils.encodeURI(rootCategory.slug) ++ "/"}>
          {String.uppercase(rootCategory.name) |> text}
        </TextLink>
        <Text style=styles##actions>
          <TextLink style=styles##action href="#like">
            <SVGFavorite fill="#ddd" width=16. height=16. />
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
            <SVGSpeechBubbleOutline fill="#ddd" width=16. height=16. />
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
      <Spacer />
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
      <Spacer size=L />
      <View style=styles##tags>
        {
          Belt.List.map(item.terms.tags, tag =>
            <Text key={tag.slug}>
              <TextLink
                style=styles##tag
                href={"/tags/" ++ Utils.encodeURI(tag.slug) ++ "/"}>
                {"#" ++ tagifyString(tag.name) |> text}
              </TextLink>
              {" " |> text}
            </Text>
          )
          ->Belt.List.toArray
          ->ReasonReact.array
        }
      </View>
      <Spacer size=XXL />
      <Author />
      <Spacer size=XXL />
      <PostComments postId={item.id} />
    </View>;
  },
};
