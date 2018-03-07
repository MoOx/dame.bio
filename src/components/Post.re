open BsReactNative;

open Helpers;

let apiBaseUrl = "https://dame.bio/";

type action =
  | Fetch
  | PostFetched(Structures.post)
  | FetchError(string);

type state = {
  fetching: bool,
  post: option(Structures.post),
  error: option(string)
};

external toExn : Js.Promise.error => Js.Exn.t = "%identity";

let fetchPost = (id, postFetched, failure) =>
  Js.Promise.(
    Fetch.fetch(apiBaseUrl ++ "wp-json/wp/v2/posts?_embed&slug=" ++ id)
    |> then_(response => Fetch.Response.json(response))
    |> then_(json =>
         json |> Structures.decodePosts |> List.hd |> postFetched |> resolve
       )
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("Post");

let make = (~splat, _children) => {
  ...component,
  initialState: () => {fetching: false, post: None, error: None},
  reducer: (action, state) =>
    switch action {
    | Fetch =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true},
        (
          ({send}) =>
            fetchPost(
              splat,
              post => send(PostFetched(post)),
              error => send(FetchError(error))
            )
            |> ignore
        )
      )
    | PostFetched(post) =>
      ReasonReact.Update({fetching: false, post: Some(post), error: None})
    | FetchError(err) =>
      ReasonReact.Update({fetching: false, post: None, error: Some(err)})
    },
  didMount: ({send}) => {
    send(Fetch) |> ignore;
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <Background>
      <CommonThings />
      <Header />
      <Container>
        <MainContent>
          (
            state.fetching ? <Text> ("Chargement ..." |> text) </Text> : nothing
          )
          (
            switch state.error {
            | None => nothing
            | Some(error) => <Text> (error |> text) </Text>
            }
          )
          (
            switch state.post {
            | None => nothing
            | Some(post) => <PostDetail post />
            }
          )
        </MainContent>
        <Sidebar />
      </Container>
      <Footer />
    </Background>
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~splat=jsProps##params##splat, [||])
  );
