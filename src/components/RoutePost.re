open BsReactNative;

open Helpers;

type action =
  | Fetch
  | PostFetched(Structures.post)
  | FetchError(string);

type state = {
  splat: string,
  fetching: bool,
  post: option(Structures.post),
  error: option(string),
};

let fetchPost = (id, postFetched, failure) =>
  Js.Promise.(
    Fetch.fetch(apiBaseUrl ++ "wp-json/wp/v2/posts?_embed&slug=" ++ id)
    |> then_(response => Fetch.Response.json(response))
    |> then_(json =>
         json
         |> Structures.decodePosts
         |> Belt.List.head
         |> postFetched
         |> resolve
       )
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("RoutePost");

let make = (~splat, _children) => {
  ...component,
  initialState: () => {splat, fetching: false, post: None, error: None},
  reducer: (action, state) =>
    switch (action) {
    | Fetch =>
      ReasonReact.UpdateWithSideEffects(
        {splat, fetching: true, post: None, error: None},
        (
          ({send}) =>
            fetchPost(
              splat,
              post =>
                switch (post) {
                | Some(post) => send(PostFetched(post))
                | None => send(FetchError("Aucun article trouvé"))
                },
              error => send(FetchError(error)),
            )
            |> ignore
        ),
      )
    | PostFetched(post) =>
      ReasonReact.Update({
        ...state,
        fetching: false,
        post: Some(post),
        error: None,
      })
    | FetchError(err) =>
      ReasonReact.Update({
        ...state,
        fetching: false,
        post: None,
        error: Some(err),
      })
    },
  didMount: ({send}) => send(Fetch),
  didUpdate: ({newSelf}) =>
    if (newSelf.state.splat != splat) {
      newSelf.send(Fetch);
    },
  render: ({state}) =>
    <WebsiteWrapper>
      {state.fetching ? <LoadingIndicator /> : nothing}
      {
        switch (state.error) {
        | None => nothing
        | Some(error) => <Text> {error |> text} </Text>
        }
      }
      {
        switch (state.post) {
        | None => nothing
        | Some(item) => <PostDetail key={item.slug} item />
        }
      }
    </WebsiteWrapper>,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~splat=jsProps##params##splat, [||])
  );
