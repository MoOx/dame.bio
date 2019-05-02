open Belt;

type action =
  | Reply;

type state =
  | None
  | ReplyOpen;

let component = ReasonReact.reducerComponent("CommentWithReplyAndChildren");

// [@react.component]
// let rec make = (~comment, ~postId, ~parentCommentId: int, ~comments) => {
[@bs.obj]
external makeProps:
  (
    ~comment: 'comment,
    ~comments: 'comments,
    ~postId: 'postId,
    ~parentCommentId: int,
    ~key: string=?,
    unit
  ) =>
  {
    .
    "comment": 'comment,
    "comments": 'comments,
    "postId": 'postId,
    "parentCommentId": int,
  } =
  "";

let rec make = props => {
  let comment = props##comment;
  let postId = props##postId;
  let parentCommentId = props##parentCommentId;
  let comments = props##comments;
  ReactCompat.useRecordApi({
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
         | None => React.null
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
             c->Option.mapWithDefault(React.null, comment =>
               comment##parent
               ->Option.flatMap(p => p##commentId)
               ->Option.getWithDefault(0)
               == parentCommentId
                 ? React.createElement(
                     make,
                     makeProps(
                       ~comment,
                       ~comments,
                       ~postId,
                       ~parentCommentId=
                         comment##commentId->Option.getWithDefault(0),
                       ~key=
                         string_of_int(
                           comment##commentId->Option.getWithDefault(index),
                         ),
                       (),
                     ),
                   )
                 : React.null
             )
           )
         ->React.array}
      </>,
  });
};
