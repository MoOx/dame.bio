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

  let (replyOpen, replyOpen_set) = React.useState()

  <>
    <Comment
      comment
      separator={comment.parent->Option.isNone}
      canReply=true
      onReply={_ => replyOpen_set(_ => true)}
    />
    {replyOpen
      ? <CommentForm databaseId parentCommentId={comment.commentId->Option.getWithDefault(0)} />
      : React.null}
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
  </>
}
