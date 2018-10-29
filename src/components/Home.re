open BsReactNative;

open Helpers;

let apiBaseUrl = "https://dame.bio/";

type action =
  | Fetch
  | PostsFetched(list(Structures.post))
  | NbPostsFetched(int)
  | PreviousPage
  | NextPage
  | FetchError(string);

type state = {
  fetching: bool,
  posts: list(Structures.post),
  page: int,
  nbTotal: int,
  error: option(string),
};

let per_page = 8;

external toExn: Js.Promise.error => Js.Exn.t = "%identity";

let fetchPosts = (page, postsFetched, nbPostsFetched, failure) =>
  Js.Promise.(
    Fetch.fetch(
      apiBaseUrl
      ++ "wp-json/wp/v2/posts?_embed"
      ++ "&per_page="
      ++ string_of_int(per_page)
      ++ "&page="
      ++ string_of_int(page),
    )
    |> then_(response => {
         let wpTotal =
           Fetch.Response.headers(response)
           |> Fetch.Headers.get("X-WP-Total");
         switch (wpTotal) {
         | None => nbPostsFetched(0)
         | Some(nb) => nbPostsFetched(int_of_string(nb))
         };
         Fetch.Response.json(response);
       })
    |> then_(json =>
         json |> Structures.decodePosts |> postsFetched |> resolve
       )
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("Home");

let make = _children => {
  let nextPagePress = (_event, self) => self.ReasonReact.send(NextPage);
  let previousPagePress = (_event, self) =>
    self.ReasonReact.send(PreviousPage);
  {
    ...component,
    initialState: () => {
      fetching: false,
      page: 1,
      posts: [],
      nbTotal: 0,
      error: None,
    },
    reducer: (action, state) =>
      switch (action) {
      | Fetch =>
        ReasonReact.UpdateWithSideEffects(
          {...state, fetching: true},
          (
            ({send}) =>
              fetchPosts(
                state.page,
                posts => send(PostsFetched(posts)),
                nb => send(NbPostsFetched(nb)),
                error => send(FetchError(error)),
              )
              |> ignore
          ),
        )
      | NbPostsFetched(nbTotal) => ReasonReact.Update({...state, nbTotal})
      | PreviousPage =>
        ReasonReact.UpdateWithSideEffects(
          {...state, page: state.page - 1},
          (({send}) => send(Fetch)),
        )
      | NextPage =>
        ReasonReact.UpdateWithSideEffects(
          {...state, page: state.page + 1},
          (({send}) => send(Fetch)),
        )
      | PostsFetched(posts) =>
        ReasonReact.Update({...state, fetching: false, posts, error: None})
      | FetchError(err) =>
        ReasonReact.Update({
          ...state,
          fetching: false,
          posts: [],
          error: Some(err),
        })
      },
    didMount: ({send}) => send(Fetch),
    render: ({state, handle}) =>
      <View>
        <CommonThings />
        <Header />
        <Container>
          <MainContent>
            {
              state.fetching ?
                <Text> {"Chargement ..." |> text} </Text> : nothing
            }
            {
              switch (state.error) {
              | None => nothing
              | Some(error) => <Text> {error |> text} </Text>
              }
            }
            {
              List.length(state.posts) > 0 ?
                <PostList posts={state.posts} /> : nothing
            }
            <View
              style=Style.(
                style([flexDirection(Row), justifyContent(SpaceAround)])
              )>
              {
                state.page > 1 ?
                  <BannerButton onPress={handle(previousPagePress)}>
                    {"Articles plus récents" |> text}
                  </BannerButton> :
                  nothing
              }
              {
                state.nbTotal > state.page * per_page ?
                  <BannerButton onPress={handle(nextPagePress)}>
                    {"Encore plus d'articles" |> text}
                  </BannerButton> :
                  nothing
              }
            </View>
          </MainContent>
          <Sidebar />
        </Container>
        <Footer />
      </View>,
  };
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make());
