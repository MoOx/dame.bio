open BsReactNative;

open Helpers;

type action =
  | Fetching
  | Fetched(list(Structures.post))
  | Errored(string);

type state = {
  fetching: bool,
  items: option(list(Structures.post)),
  error: option(string),
};

let fetchData = (id, success, failure) =>
  Js.Promise.(
    Fetch.fetch(
      apiBaseUrl
      ++ "wp-json/related-posts-by-taxonomy/v1/posts/"
      ++ string_of_int(id)
      ++ "?posts_per_page=4&format=json&title=&before_shortcode=&after_shortcode=",
    )
    |> then_(response => Fetch.Response.json(response))
    |> then_(json =>
         json |> Structures.decodeRelatedPosts |> success |> resolve
       )
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("PostRelatedPosts");

let make = (~postId, _children) => {
  ...component,
  initialState: () => {fetching: false, items: None, error: None},
  reducer: (action, state) =>
    switch (action) {
    | Fetching =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true},
        (
          ({send}) =>
            fetchData(
              postId,
              items => send(Fetched(items)),
              error => send(Errored(error)),
            )
            |> ignore
        ),
      )
    | Fetched(items) =>
      ReasonReact.Update({fetching: false, items: Some(items), error: None})
    | Errored(err) =>
      ReasonReact.Update({fetching: false, items: None, error: Some(err)})
    },
  didMount: ({send}) => send(Fetching),
  render: ({state}) =>
    <>
      {state.fetching ? <LoadingIndicator /> : nothing}
      {
        switch (state.error) {
        | None => nothing
        | Some(error) => <Text> {error |> text} </Text>
        }
      }
      {
        switch (state.items) {
        | None => nothing
        | Some(items) => <RelatedPosts items />
        }
      }
    </>,
};

