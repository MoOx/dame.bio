open Helpers;

type action =
  | Reply;

type state =
  | None
  | ReplyOpen;

let component = ReasonReact.reducerComponent("PostComment");

let rec make =
        (
          ~comment: Structures.comment,
          ~postId,
          ~parentCommentId,
          ~comments: list(Structures.comment),
          _,
        ) => {
  ...component,
  initialState: () => None,
  reducer: (action, _) =>
    switch (action) {
    | Reply => ReasonReact.Update(ReplyOpen)
    },
  render: ({state, send}) =>
    <>
      <Comment
        comment
        separator={comment.parent == 0}
        canReply=true
        onReply={() => send(Reply) |> ignore}
      />
      {switch (state) {
       | None => nothing
       | ReplyOpen => <CommentForm postId parentCommentId={comment.id} />
       }}
      {comments
       ->Belt.List.reverse
       ->Belt.List.map(comment =>
           comment.parent == parentCommentId ?
             ReasonReact.element(
               ~key=string_of_int(comment.id),
               make(
                 ~comment,
                 ~postId,
                 ~comments,
                 ~parentCommentId=comment.id,
                 [||],
               ),
             ) :
             nothing
         )
       ->Belt.List.toArray
       ->ReasonReact.array}
    </>,
};
