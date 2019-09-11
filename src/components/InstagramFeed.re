open Belt;
open BsReactNative;

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

let count = 14;

let component = ReasonReact.reducerComponent("InstagramFeed");

let styles =
  Style.(
    StyleSheet.create({
      "blockTitle":
        style([
          fontSize(Float(12.)),
          fontWeight(`_800),
          color(String(Consts.Colors.grey)),
          opacity(Float(0.75)),
        ]),
      "items": style([flexDirection(Row)]),
    })
  );

let fetchData = (success, failure) =>
  Js.Promise.(
    Utils.fetchJsonp(
      "https://api.instagram.com/v1/users/2129304591/media/recent?access_token=2129304591.6e128d6.673b14118bd848028911564d7001ffe0&count="
      ++ count->string_of_int,
    )
    |> then_(Fetch.Response.json)
    |> then_(json => Obj.magic(json)##data |> success |> resolve)
    |> catch(err => {
         Js.log(err);
         failure("Une erreur est survenue") |> resolve;
       })
  );

[@react.component]
let make = () =>
  ReactCompat.useRecordApi({
    ...component,
    initialState: () => {fetching: false, items: None, error: None},
    reducer: (action, state) =>
      switch (action) {
      | Fetching =>
        ReasonReact.UpdateWithSideEffects(
          {...state, fetching: true},
          ({send}) =>
            fetchData(
              items => send(Fetched(items)),
              error => send(Errored(error)),
            )
            |> ignore,
        )
      | Fetched(items) =>
        ReasonReact.Update({
          fetching: false,
          items: Some(items),
          error: None,
        })
      | Errored(err) =>
        ReasonReact.Update({fetching: false, items: None, error: Some(err)})
      },
    didMount: ({send}) => send(Fetching),
    render: ({state}) =>
      <View>
        {switch (state.error) {
         | None => React.null
         | Some(error) =>
           Js.log2("Instagram", error);
           React.null;
         }}
        {switch (state.items) {
         | None => React.null
         | Some(items) =>
           switch (items) {
           | [||] => React.null
           | _ =>
             let size =
               Dimensions.get(`window)##width->float_of_int->min(293.);

             <View>
               <SpacedView horizontal=XS vertical=XS>
                 <TextLink
                   style=styles##blockTitle
                   href="https://instagram.com/dame.bio">
                   {j|INSTAGRAM / @dame.bio|j}->React.string
                 </TextLink>
               </SpacedView>
               <div className="ScrollView-snapToAlignment-center">
                 <ScrollView
                   horizontal=true
                   pagingEnabled=true
                   style=Style.(
                     array([|styles##items, style([height(Pt(size))])|])
                   )>
                   {{items->Array.map(item =>
                       <InstagramPost key=item##id item size />
                     )}
                    ->React.array}
                 </ScrollView>
               </div>
             </View>;
           }
         }}
      </View>,
  });
