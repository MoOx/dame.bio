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
              <Text>
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
                <PostComment key={string_of_int(comment.id)} comment postId />
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
