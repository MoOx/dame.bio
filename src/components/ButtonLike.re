open BsReactNative;

let defaultSize = 14.;

let defaultColor = "#999";

let styles =
  StyleSheet.create(Style.{"touchable": style([justifyContent(Center)])});

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
  | NotLiked
  | Liked;

type action =
  | Like
  | Unlike;

let component = ReasonReact.reducerComponent("LikeButton");

let make = (~id, ~size=defaultSize, _) => {
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
            | NotLiked =>
              <TouchableScale
                style=styles##touchable
                activeScale=1.5
                hoverScale=1.1
                focusScale=1.1
                onPress={_ => {
                  like(~variables=likeMutation##variables, ()) |> ignore;
                  send(Like);
                }}>
                <SVGFavoriteOutline fill=defaultColor width=size height=size />
              </TouchableScale>
            | Liked =>
              <TouchableScale
                style=styles##touchable
                activeScale=0.75
                hoverScale=1.1
                focusScale=1.1
                onPress={_ => {
                  unlike(~variables=unlikeMutation##variables, ()) |> ignore;
                  send(Unlike);
                }}>
                <SVGFavorite fill="#E2254D" width=size height=size />
              </TouchableScale>
            };
          }}
        </UnlikePostMutation>;
      }}
    </LikePostMutation>,
};
