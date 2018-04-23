open Helpers;

open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.(
      {
        "block":
          style([
            flex(1.),
            flexBasis(Pt(350.)),
            borderWidth(0.75),
            borderColor("#EBEBEB"),
            backgroundColor("#FFF"),
            marginRight(Pt(40.)),
            marginBottom(Pt(40.))
          ]),
        "row": style([flexDirection(Row), justifyContent(SpaceBetween)]),
        "text": style([padding(Pt(20.))]),
        "category":
          style([
            marginBottom(Pt(10.)),
            fontSize(Float(10.)),
            color("#DE6D88")
          ]),
        "actions":
          style([
            display(Flex),
            flexDirection(Row),
            marginBottom(Pt(10.)),
            fontSize(Float(10.)),
            color("#bbb")
          ]),
        "action":
          style([display(Flex), flexDirection(Row), marginHorizontal(Pt(4.))]),
        "title":
          style([
            fontFamily("IndieFlower"),
            fontSize(Float(22.)),
            lineHeight(28.),
            color("#524D43")
          ]),
        "link": style([padding(Pt(10.))])
      }
    )
  );

let findMainTag = (item: Structures.post) : Structures.term =>
  List.find(
    (term: Structures.term) => ! term.hasParent,
    item.terms.categories
  );

let component = ReasonReact.statelessComponent("PostPreview");

let make = (~item: Structures.post, _) => {
  ...component,
  render: _self => {
    let mainTag = findMainTag(item);
    let href =
      "/"
      ++ String.lowercase(mainTag.slug)
      ++ "/"
      ++ String.lowercase(item.slug)
      ++ "/";
    <View key=(string_of_int(item.id)) style=styles##block>
      <TextLink href>
        <ImageWithAspectRatio
          uri=List.hd(item.featuredMedia).media_details.sizes.medium.source_url
        />
      </TextLink>
      <View style=styles##text>
        <View style=styles##row>
          <TextLink
            style=styles##category
            href=("/tag/" ++ Utils.encodeURI(mainTag.slug))>
            (String.uppercase(mainTag.name) |> text)
          </TextLink>
          <Text style=styles##actions>
            <TextLink style=styles##action href="#like">
              <SVGFavorite fill="#ddd" width=12. height=12. />
              (
                (
                  if (item.likes != 0) {
                    " " ++ (item.likes |> string_of_int);
                  } else {
                    "";
                  }
                )
                |> text
              )
            </TextLink>
            <Text style=styles##action> (" | " |> text) </Text>
            <TextLink style=styles##action href=(href ++ "#comments")>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
              (
                switch item.comments {
                | None => "" |> text
                | Some(comments) =>
                  " " ++ (List.length(comments) |> string_of_int) |> text
                }
              )
            </TextLink>
          </Text>
        </View>
        <TextLink style=styles##title href> (item.title |> text) </TextLink>
      </View>
    </View>;
  }
};
