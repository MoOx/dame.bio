open BsReactNative;

type action =
  | Fetching
  | Errored(string)
  | Fetched(list(Structures.post));

type state =
  | Empty
  | Loading
  | Error(string)
  | Data(list(Structures.post));

let fetchData = (id, success, failure) =>
  Js.Promise.(
    Fetch.fetch(
      "https://dame.bio/wp-json/related-posts-by-taxonomy/v1/posts/"
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

let make = (~postId, ~hasBeenVisible, _children) => {
  ...component,
  initialState: () => Empty,
  reducer: (action, _) =>
    switch (action) {
    | Fetching =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        ({send}) =>
          fetchData(
            postId,
            items => send(Fetched(items)),
            error => send(Errored(error)),
          )
          |> ignore,
      )
    | Fetched(items) => ReasonReact.Update(Data(items))
    | Errored(err) => ReasonReact.Update(Error(err))
    },
  didUpdate: ({newSelf: {send, state}}) =>
    switch (state) {
    | Empty when hasBeenVisible => send(Fetching)
    | _ => ()
    },
  render: ({state}) =>
    switch (state) {
    | Empty
    | Loading =>
      <RelatedPosts
        items=[
          Structures.placeholderPost(-1),
          Structures.placeholderPost(-2),
          Structures.placeholderPost(-3),
          Structures.placeholderPost(-4),
        ]
      />
    | Error(e) => <Text> e->ReasonReact.string </Text>
    | Data(items) => <RelatedPosts items />
    },
};
