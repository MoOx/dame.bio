type action =
  | Reply;

type state =
  | None
  | ReplyOpen;

let component = ReasonReact.reducerComponent("CommentWithReplyAndChildren");

let rec make = (~comment, ~postId, ~parentCommentId: int, ~comments, _) => {
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
        separator={comment##parent->Belt.Option.isNone}
        canReply=true
        onReply={() => send(Reply) |> ignore}
      />
      {switch (state) {
       | None => ReasonReact.null
       | ReplyOpen =>
         <CommentForm
           postId
           parentCommentId={comment##commentId->Belt.Option.getWithDefault(0)}
         />
       }}
      {comments
       ->Belt.Option.flatMap(ts => ts##nodes)
       ->Belt.Option.getWithDefault([||])
       ->Belt.Array.mapWithIndex((index, c) =>
           c->Belt.Option.mapWithDefault(ReasonReact.null, comment =>
             comment##parent
             ->Belt.Option.flatMap(p => p##commentId)
             ->Belt.Option.getWithDefault(0)
             == parentCommentId ?
               ReasonReact.element(
                 ~key=
                   string_of_int(
                     comment##commentId->Belt.Option.getWithDefault(index),
                   ),
                 make(
                   ~comment,
                   ~postId,
                   ~comments,
                   ~parentCommentId=
                     comment##commentId->Belt.Option.getWithDefault(0),
                   [||],
                 ),
               ) :
               ReasonReact.null
           )
         )
       ->ReasonReact.array}
    </>,
};
