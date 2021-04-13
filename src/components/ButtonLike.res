open ReactNative
let defaultSize = 14.
let defaultColor = Consts.Colors.grey
let styles = {
  open Style
  StyleSheet.create({"touchable": style(~justifyContent=#center, ())})
}
module LikePost = %graphql(`
  mutation like($id: ID!) {
    likePost(input: {clientMutationId: "likePost", id: $id}) {
      post {
        id
        title
        likeCount
      }
    }
  }
`)
module UnlikePost = %graphql(`
  mutation like($id: ID!) {
    unlikePost(input: {clientMutationId: "unlikePost", id: $id}) {
      post {
        id
        title
        likeCount
      }
    }
  }
`)
type state =
  | NotLiked
  | Liked
type action =
  | Like
  | Unlike
@react.component
let make = (~id, ~size=defaultSize) => {
  let (isLiked, isLiked_set) = React.useState(() => Likes.isLiked(id))
  let (like, _like_result) = LikePost.use()
  let (unlike, _unlike_result) = UnlikePost.use()
  !isLiked
    ? <TouchableScale
        style={styles["touchable"]}
        activeScale=1.5
        hoverScale=1.1
        focusScale=1.1
        onPress={_ => {
          like({id: id})->ignore
          isLiked_set(_ => true)
        }}>
        <SVGFavoriteOutline
          fill=defaultColor width={size->Js.Float.toString} height={size->Js.Float.toString}
        />
      </TouchableScale>
    : <TouchableScale
        style={styles["touchable"]}
        activeScale=0.75
        hoverScale=1.1
        focusScale=1.1
        onPress={_ => {
          unlike({id: id})->ignore
          isLiked_set(_ => false)
        }}>
        <SVGFavorite
          fill="#E2254D" width={size->Js.Float.toString} height={size->Js.Float.toString}
        />
      </TouchableScale>
}
