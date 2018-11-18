open BsReactNative;

open Helpers;

let styles =
  StyleSheet.create(
    Style.{"items": style([height(Pt(293.)), flexDirection(Row)])},
  );

type item = {
  .
  "id": string,
  /*
   "user": {
     .
     "id": string,
     "full_name": string,
     "profile_picture": string,
     "username": string,
   },
   */
  "images": {
    .
    /*
     "thumbnail": {
       .
       "width": int,
       "height": int,
       "url": string,
     },
     "low_resolution": {
       .
       "width": int,
       "height": int,
       "url": string,
     },
     */
    "standard_resolution": {
      .
      "width": int,
      "height": int,
      "url": string,
    },
  },
  /* "created_time": string, */
  /*
   "caption": {
     .
     "id": string,
     "text": string,
     "created_time": string,
     "from": {
       .
       "id": string,
       "full_name": string,
       "profile_picture": string,
       "username": string,
     },
   },
   */
  /* "user_has_liked": bool, */
  "likes": {. "count": int},
  /* "tags": Js.Array.t(string), */
  /* "filter": string, */
  "comments": {. "count": int},
  /* "type": string, */
  "link": string,
  /* "location": Js.nullable(string),
     "attribution": Js.nullable(string), */
  /* "users_in_photo": Js.Array.t(string), */
};

type action =
  | Fetching
  | Fetched(Js.Array.t(item))
  | Errored(string);

type state = {
  fetching: bool,
  items: option(Js.Array.t(item)),
  error: option(string),
};

let fetchData = (success, failure) =>
  Js.Promise.(
    Fetch.fetch(
      "https://api.instagram.com/v1/users/2129304591/media/recent?access_token=2129304591.6e128d6.673b14118bd848028911564d7001ffe0&count=10",
    )
    |> then_(response => Fetch.Response.json(response))
    |> then_(json => Obj.magic(json)##data |> success |> resolve)
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("InstagramFeed");

let make = _children => {
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
    <View>
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
        | Some(items) =>
          switch (items) {
          | [||] => nothing
          | _ =>
            <ScrollView horizontal=true style=styles##items>
              {
                items
                ->Belt.Array.map(item => <InstagramPost key=item##id item />)
                ->ReasonReact.array
              }
            </ScrollView>
          }
        }
      }
    </View>,
};
