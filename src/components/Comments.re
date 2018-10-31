open Helpers;

open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "comments": style([]),
      "comment": style([flexDirection(Row)]),
      "commentAvatar":
        style([width(Pt(48.)), height(Pt(48.)), borderRadius(100.)]),
      "commentTextContainer": style([flex(1.)]),
      "commentLink":
        style([color(String("#524D43")), textDecorationLine(Style.None)]),
      "commentDate":
        style([
          fontSize(Float(11.)),
          color(String("rgb(170, 170, 170)")),
        ]),
      "commentContent": style([flexShrink(1.)]),
    },
  );

let component = ReasonReact.statelessComponent("Comments");

let make = (~comments: Structures.comments, _) => {
  ...component,
  render: _self =>
    <View style=styles##comments>
      {
        switch (comments) {
        | None => <Text> {"Pas de commentaires" |> text} </Text>
        | Some(comments) =>
          comments
          |> List.map((comment: Structures.comment) =>
               <View key={string_of_int(comment.id)} style=styles##comment>
                 <Image
                   style=styles##commentAvatar
                   resizeMode=`contain
                   source={
                            `URI(
                              Image.(
                                imageURISource(
                                  ~uri=comment.author_avatar_url,
                                  (),
                                )
                              ),
                            )
                          }
                 />
                 <Spacer />
                 <View style=styles##commentTextContainer>
                   <TextLink
                     href={comment.author_url} style=styles##commentLink>
                     {comment.author_name |> text}
                   </TextLink>
                   <Text style=styles##commentDate>
                     {comment.date |> Date.relativeDate |> text}
                   </Text>
                   <Text style=styles##commentContent>
                     <div
                       className="dbComment"
                       dangerouslySetInnerHTML={"__html": comment.content}
                     />
                   </Text>
                 </View>
               </View>
             )
          |> Array.of_list
          |> ReasonReact.array
        }
      }
    </View>,
};
