open BsReactNative;

open Helpers;

type action =
  | Fetch
  | CommentsFetched(Structures.comments)
  | FetchError(string);

type state = {
  fetching: bool,
  comments: option(Structures.comments),
  error: option(string),
};

let fetchComments = (id, commentsFetched, failure) =>
  Js.Promise.(
    Fetch.fetch(
      apiBaseUrl
      ++ "wp-json/wp/v2/comments?per_page=100&post="
      ++ string_of_int(id),
    )
    |> then_(response => Fetch.Response.json(response))
    |> then_(json =>
         json |> Structures.decodeComments |> commentsFetched |> resolve
       )
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("PostComments");

let make = (~postId, _children) => {
  ...component,
  initialState: () => {fetching: false, comments: None, error: None},
  reducer: (action, state) =>
    switch (action) {
    | Fetch =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true},
        ({send}) =>
          fetchComments(
            postId,
            comments => send(CommentsFetched(comments)),
            error => send(FetchError(error)),
          )
          |> ignore,
      )
    | CommentsFetched(comments) =>
      ReasonReact.Update({
        fetching: false,
        comments: Some(comments),
        error: None,
      })
    | FetchError(err) =>
      ReasonReact.Update({fetching: false, comments: None, error: Some(err)})
    },
  didMount: ({send}) => send(Fetch),
  render: ({state}) =>
    <View>
      <a name="comments" />
      {state.fetching ? <LoadingIndicator /> : nothing}
      {switch (state.error) {
       | None => nothing
       | Some(error) => <Text> {error |> text} </Text>
       }}
      {switch (state.comments) {
       | None => nothing
       | Some(comments) => <Comments postId comments />
       }}
    </View>,
};
