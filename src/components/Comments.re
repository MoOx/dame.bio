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

let make = (~postId, ~commentCounts, ~comments, _) => {
  ...component,
  render: _self =>
    <>
      /* @todo native fix */
      <a name="comments" />
      <View>
        <Text style=styles##subtitle>
          {(
             switch (commentCounts->Belt.Option.getWithDefault(0)) {
             | 0 => "Commentaires"
             | 1 => "1 Commentaire"
             | count => count->string_of_int ++ " Commentaires"
             }
           )
           |> text}
        </Text>
      </View>
      <Spacer size=S />
      <View style=styles##comments>
        {switch (
           comments
           ->Belt.Option.flatMap(ts => ts##nodes)
           ->Belt.Option.getWithDefault([||])
         ) {
         | [||] =>
           <>
             <Spacer size=L />
             <Text style=styles##noComment>
               {"Aucun commentaire pour l'instant. Laissez le votre !" |> text}
             </Text>
             <Spacer size=L />
           </>
         | coms =>
           coms
           ->Belt.Array.reverse
           ->Belt.Array.mapWithIndex((index, comment) =>
               comment->Belt.Option.mapWithDefault(nothing, comment =>
                 comment##parent->Belt.Option.isNone ?
                   <CommentWithReplyAndChildren
                     key={string_of_int(
                       comment##commentId->Belt.Option.getWithDefault(index),
                     )}
                     comment
                     parentCommentId={
                       comment##commentId->Belt.Option.getWithDefault(0)
                     }
                     postId
                     comments
                   /> :
                   nothing
               )
             )
           ->ReasonReact.array
         }}
        <CommentSeparator />
        <Spacer />
        <CommentForm postId parentCommentId=0 />
      </View>
    </>,
};
