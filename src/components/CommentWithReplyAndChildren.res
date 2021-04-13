open Belt

type action = Reply

type state =
  | None
  | ReplyOpen

type props<'comment, 'databaseId> = {
  "comment": 'comment,
  "comments": option<WPGraphQL.PostDetailFragment.t_comments>,
  "databaseId": 'databaseId,
  "parentCommentId": int,
}

// [@react.component]
// let rec make = (~comment, ~databaseId, ~parentCommentId: int, ~comments) => {
@obj
external makeProps: (
  ~comment: 'comment,
  ~comments: option<WPGraphQL.PostDetailFragment.t_comments>,
  ~databaseId: 'databaseId,
  ~parentCommentId: int,
  ~key: string=?,
  unit,
) => props<'comment, 'databaseId> = ""

let rec make = (props: props<'comment, 'databaseId>) => {
  let comment = props["comment"]
  let databaseId = props["databaseId"]
  let parentCommentId = props["parentCommentId"]
  let comments = props["comments"]

  ReactCompat.useRecordApi({
    ...ReactCompat.component,
    initialState: () => None,
    reducer: (action, _) =>
      switch action {
      | Reply => ReactCompat.Update(ReplyOpen)
      },
    render: ({state, send}) => <>
      <Comment
        comment
        separator={comment.parent->Option.isNone}
        canReply=true
        onReply={_ => send(Reply) |> ignore}
      />
      {switch state {
      | None => React.null
      | ReplyOpen =>
        <CommentForm databaseId parentCommentId={comment.commentId->Option.getWithDefault(0)} />
      }}
      {comments
      ->Option.flatMap(ts => ts.nodes)
      ->Option.getWithDefault([])
      ->Array.mapWithIndex((index, c) =>
        c->Option.mapWithDefault(React.null, comment =>
          comment.parent->Option.flatMap(p => p.commentId)->Option.getWithDefault(0) ==
            parentCommentId
            ? React.createElement(
                make,
                makeProps(
                  ~comment,
                  ~comments,
                  ~databaseId,
                  ~parentCommentId=comment.commentId->Option.getWithDefault(0),
                  ~key=string_of_int(comment.commentId->Option.getWithDefault(index)),
                  (),
                ),
              )
            : React.null
        )
      )
      ->React.array}
    </>,
  })
}
