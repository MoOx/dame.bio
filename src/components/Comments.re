open Helpers;

open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "comments": style([]),
      "subtitle":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(28.)),
          lineHeight(28. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
      "noComment":
        style([
          textAlign(Center),
          fontSize(Float(18.)),
          color(String("#d6d5d2")),
          fontWeight(`_600),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Comments");

let make = (~postId, ~comments: Structures.comments, _) => {
  ...component,
  render: _self =>
    <>
      <View>
        <Text style=styles##subtitle> {"Commentaires" |> text} </Text>
      </View>
      <Spacer size=S />
      <View style=styles##comments>
        {
          switch (comments) {
          | [] =>
            <>
              <Spacer size=L />
              <Text style=styles##noComment>
                {
                  "Aucun commentaire pour l'instant. Laissez le votre !" |> text
                }
              </Text>
              <Spacer size=L />
            </>
          | _ =>
            comments
            ->Belt.List.reverse
            ->Belt.List.map(comment =>
                comment.parent == 0 ?
                  <PostComment
                    key={string_of_int(comment.id)}
                    comment
                    parentCommentId={comment.id}
                    postId
                    comments
                  /> :
                  nothing
              )
            ->Belt.List.toArray
            ->ReasonReact.array
          }
        }
        <CommentSeparator />
        <Spacer />
        <CommentForm postId parentCommentId=0 />
      </View>
    </>,
};
