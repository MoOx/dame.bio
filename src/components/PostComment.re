open Helpers;

type action =
  | Reply;

type state =
  | None
  | ReplyOpen;

let component = ReasonReact.reducerComponent("PostComment");

let make = (~comment: Structures.comment, ~postId, _) => {
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
      {
        switch (state) {
        | None => nothing
        | ReplyOpen => <CommentForm postId parentCommentId={comment.id} />
        }
      }
    </>,
};
