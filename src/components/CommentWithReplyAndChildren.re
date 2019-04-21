open Belt;

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
        separator={comment##parent->Option.isNone}
        canReply=true
        onReply={_ => send(Reply) |> ignore}
      />
      {switch (state) {
       | None => ReasonReact.null
       | ReplyOpen =>
         <CommentForm
           postId
           parentCommentId={comment##commentId->Option.getWithDefault(0)}
         />
       }}
      {comments
       ->Option.flatMap(ts => ts##nodes)
       ->Option.getWithDefault([||])
       ->Array.mapWithIndex((index, c) =>
           c->Option.mapWithDefault(ReasonReact.null, comment =>
             comment##parent
             ->Option.flatMap(p => p##commentId)
             ->Option.getWithDefault(0)
             == parentCommentId
               ? ReasonReact.element(
                   ~key=
                     string_of_int(
                       comment##commentId->Option.getWithDefault(index),
                     ),
                   make(
                     ~comment,
                     ~postId,
                     ~comments,
                     ~parentCommentId=
                       comment##commentId->Option.getWithDefault(0),
                     [||],
                   ),
                 )
               : ReasonReact.null
           )
         )
       ->ReasonReact.array}
    </>,
};
