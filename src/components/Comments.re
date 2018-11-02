open Helpers;

open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "comments": style([]),
      "row": style([flexDirection(Row)]),
      "comment": style([flexDirection(Row)]),
      "commentSeparator":
        style([
          flex(1.),
          height(Pt(1.)),
          backgroundColor(String("#f4f4f4")),
          marginHorizontal(Pt(50.)),
        ]),
      "commentAvatar":
        style([
          width(Pt(40.)),
          height(Pt(40.)),
          borderRadius(100.),
        ]),
        "commentAvatarDefault":
          style([
            lineHeight(40.),
            color(String("#fff")),
            textAlign(Center),
            fontWeight(`_600),
            fontSize(Float(18.)),
          ]),
        "commentAvatarImage":
          style([
            position(Absolute),
            top(Pt(0.)),
            left(Pt(0.)),
            width(Pt(40.)),
            height(Pt(40.)),
            borderRadius(100.),
          ]),
      "commentTextContainer": style([flex(1.)]),
      "commentMeta": style([flexDirection(Row)]),
      "commentAuthor":
        style([
          color(String("#49443A")),
          fontWeight(`_600),
          lineHeight(24.),
          textDecorationLine(Style.None),
        ]),
      "commentOwner":
        style([
          color(String("#fff")),
          backgroundColor(String("#DE6D88")),
          paddingHorizontal(Pt(6.)),
          borderRadius(8.),
          fontSize(Float(10.)),
          fontWeight(`_300),
          lineHeight(20.),
          alignSelf(Center),
        ]),
      "commentDate":
        style([
          fontSize(Float(11.)),
          lineHeight(24.),
          color(String("#bdbdbd")),
        ]),
      "commentContent":
        style([
          flexShrink(1.),
          color(String("#49443A")),
          fontSize(Float(14.)),
          lineHeight(24.),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Comments");

let notSoRandomColor = s => {
  let hue =
    Belt.List.makeBy(String.length(s), i => s.[i])
    ->Belt.List.reduce(0, (hue, char) => hue + Char.code(char))
    mod 360;
  "hsl(" ++ string_of_int(hue) ++ ", 90%, 95%)";
};

let make = (~comments: Structures.comments, _) => {
  ...component,
  render: _self =>
    <View style=styles##comments>
      {
        switch (comments) {
        | [] => <Text> {"Pas de commentaires" |> text} </Text>
        | _ =>
          comments
          ->Belt.List.reverse
          ->Belt.List.mapWithIndex((index, comment) => {
              let isOwner = comment.author == 2;
              <View key={string_of_int(comment.id)}>
                {
                  index > 0 && comment.parent == 0 ?
                    <> <View style=styles##commentSeparator /> <Spacer /> </> :
                    nothing
                }
                <View style=styles##comment>
                  {comment.parent > 0 ? <Spacer size=XL /> : nothing}
                  <View>
                    <Spacer size=XXS />
                      <View
                        style=Style.(
                          flatten([|
                            styles##commentAvatar,
                            style([
                              backgroundColor(
                                String(notSoRandomColor(comment.author_name)),
                              ),
                            ]),
                          |])
                        )>
                        <Text style=styles##commentAvatarDefault>
                          {
                            String.sub(comment.author_name, 0, 1)
                            |> String.capitalize
                            |> text
                          }
                        </Text>
                        <Image
                          style=styles##commentAvatarImage
                          resizeMode=`contain
                          source={
                            `URI(
                              Image.(
                                imageURISource(
                                  ~uri=
                                  comment.author_avatar_url ++ "&d=blank",
                                  (),
                                )
                              ),
                            )
                          }
                        />
                      </View>
                  </View>
                  <Spacer size=XS />
                  <View style=styles##commentTextContainer>
                    <View style=styles##commentMeta>
                      <TextLink
                        href={comment.author_url} style=styles##commentAuthor>
                        {comment.author_name |> text}
                      </TextLink>
                      {
                        isOwner ?
                          <>
                            <Text> {" " |> text} </Text>
                            <TextLink
                              href={comment.author_url}
                              style=styles##commentOwner>
                              {"Auteur" |> text}
                            </TextLink>
                          </> :
                          nothing
                      }
                    </View>
                    <View style=styles##row>
                      <Text style=styles##commentDate>
                        {
                          (
                            comment.date
                            |> Date.relativeDate
                            |> String.capitalize
                          )
                          ++ {j|  ·  |j}
                          |> text
                        }
                      </Text>
                      <Text style=styles##commentDate>
                        {{j|Répondre|j} |> text}
                      </Text>
                    </View>
                    <Text style=styles##commentContent>
                      <div
                        className="dbComment"
                        dangerouslySetInnerHTML={
                          "__html":
                            comment.content
                            |> Js.String.replace("<p>", "")
                            |> Js.String.replace("</p>", ""),
                        }
                      />
                    </Text>
                  </View>
                </View>
                <Spacer />
              </View>
            })
          ->Belt.List.toArray
          ->ReasonReact.array
        }
      }
    </View>,
};
