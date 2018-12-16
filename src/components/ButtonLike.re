open BsReactNative;

module LikePost = [%graphql
  {|
  mutation like($id: ID!) {
    likePost(input: {clientMutationId: "likePost", id: $id}) {
      post {
        id
        title
        likeCount
      }
    }
  }
|}
];

module LikePostMutation = ReasonApollo.CreateMutation(LikePost);

module UnlikePost = [%graphql
  {|
  mutation like($id: ID!) {
    unlikePost(input: {clientMutationId: "unlikePost", id: $id}) {
      post {
        id
        title
        likeCount
      }
    }
  }
|}
];

module UnlikePostMutation = ReasonApollo.CreateMutation(UnlikePost);

type state =
  | Liked
  | NotLiked;

type action =
  | Like
  | Unlike;

let liked = <SVGFavorite fill="#E2254D" width=12. height=12. />;
let unliked = <SVGFavorite fill="#ddd" width=12. height=12. />;

let component = ReasonReact.reducerComponent("LikeButton");

let make = (~id, _) => {
  ...component,

  initialState: () => Likes.isLiked(id) ? Liked : NotLiked,

  reducer: (action, _) =>
    switch (action) {
    | Like => ReasonReact.UpdateWithSideEffects(Liked, _ => Likes.like(id))
    | Unlike =>
      ReasonReact.UpdateWithSideEffects(NotLiked, _ => Likes.unlike(id))
    },

  render: ({state, send}) =>
    <LikePostMutation>
      ...{(like, _) => {
        let likeMutation = LikePost.make(~id, ());
        <UnlikePostMutation>
          ...{(unlike, _) => {
            let unlikeMutation = UnlikePost.make(~id, ());
            switch (state) {
            | Liked =>
              <TouchableOpacity
                onPress={_ => {
                  unlike(~variables=unlikeMutation##variables, ()) |> ignore;
                  send(Unlike);
                }}>
                liked
              </TouchableOpacity>
            | NotLiked =>
              <TouchableOpacity
                onPress={_ => {
                  like(~variables=likeMutation##variables, ()) |> ignore;
                  send(Like);
                }}>
                unliked
              </TouchableOpacity>
            };
          }}
        </UnlikePostMutation>;
      }}
    </LikePostMutation>,
};
