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
            borderWidth(1.),
            borderColor("#F0F0EF"),
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
          style([fontSize(Float(10.)), lineHeight(12.), color("#bbb")]),
        "action": style([]),
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
    let href = "/blog/" ++ item.slug ++ "/";
    let mainTag = findMainTag(item);
    <View key=(string_of_int(item.id)) style=styles##block>
      <ImageWithAspectRatio
        uri=List.hd(item.featuredMedia).media_details.sizes.medium.source_url
      />
      <View style=styles##text>
        <View style=styles##row>
          <TextLink
            style=styles##category
            href=("/tag/" ++ Utils.encodeURI(mainTag.slug))>
            (ReasonReact.stringToElement(String.uppercase(mainTag.name)))
          </TextLink>
          <Text style=styles##actions>
            <TextLink style=styles##action href="#like">
              <SVGFavorite fill="#ddd" width=12. height=12. />
              (ReasonReact.stringToElement({j| 4|j}))
            </TextLink>
            (ReasonReact.stringToElement(" | "))
            <TextLink style=styles##action href=(href ++ "#comments")>
              <SVGSpeechBubbleOutline fill="#ddd" width=12. height=12. />
              (ReasonReact.stringToElement({j| 12|j}))
            </TextLink>
          </Text>
        </View>
        <TextLink style=styles##title href>
          (ReasonReact.stringToElement(item.title))
        </TextLink>
      </View>
    </View>;
  }
};
