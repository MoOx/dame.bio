open BsReactNative;

open Helpers;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

let per_page = 8;

type status =
  | Loading
  | Ready
  | Error;

type res = {
  total: int,
  items: list(Structures.post),
};

let fetchItems = (~page, success, failure) =>
  Fetch.fetch(
    apiBaseUrl
    ++ "wp-json/wp/v2/posts?_embed"
    ++ "&per_page="
    ++ string_of_int(per_page)
    ++ "&page="
    ++ string_of_int(page),
  )
  |> Js.Promise.then_(response =>
       Fetch.Response.json(response)
       |> Js.Promise.then_(json => {
            let total =
              switch (
                Fetch.Response.headers(response)
                |> Fetch.Headers.get("X-WP-Total")
              ) {
              | None => 0
              | Some(nb) => int_of_string(nb)
              };
            let items = json |> Structures.decodePosts;
            success({total, items}) |> Js.Promise.resolve;
          })
     )
  |> Js.Promise.catch(err => err |> failure |> Js.Promise.resolve);

type initialPropsArgs = {
  .
  "params": {
    .
    "categories": string,
    "tags": string,
  },
};

let getInitialProps = args =>
  Js.Promise.make((~resolve, ~reject) =>
    fetchItems(
      ~page=
        switch (Js.Nullable.toOption(args##params##page)) {
        | None => 1
        | Some(i) => int_of_string(i)
        },
      res => resolve(. {"total": res.total, "items": res.items}),
      err => reject(. Js.Exn.raiseError("Oops!")),
    )
    |> ignore
  );

let component = ReasonReact.statelessComponent("RoutePosts");

let make = (~status, ~page, ~total, ~items, ~error, _) => {
  ...component,
  render: _ =>
    <WebsiteWrapper>
      {
        switch (status) {
        | Loading => <LoadingIndicator />
        | Error =>
          switch (error) {
          | None => nothing
          | Some(error) => <Text> {error |> text} </Text>
          }
        | Ready =>
          switch (items) {
          | [] => nothing
          | _ =>
            <>
              <PostList posts=items />
              <View
                style=Style.(
                  style([flexDirection(Row), justifyContent(SpaceAround)])
                )>
                {
                  page > 1 ?
                    <BannerButton
                      href={
                        page == 2 ? "/" : "/page/" ++ string_of_int(page - 1)
                      }>
                      {"Articles plus récents" |> text}
                    </BannerButton> :
                    nothing
                }
                {
                  total > page * per_page ?
                    <BannerButton href={"/page/" ++ string_of_int(page + 1)}>
                      {"Encore plus d'articles" |> text}
                    </BannerButton> :
                    nothing
                }
              </View>
            </>
          }
        }
      }
    </WebsiteWrapper>,
};

let composedComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~status=
        switch (jsProps##status) {
        | "loading" => Loading
        | "ready" => Ready
        | "error"
        | _ => Error
        },
      ~page=
        switch (Js.Nullable.toOption(jsProps##params##page)) {
        | None => 1
        | Some(i) => int_of_string(i)
        },
      ~total=
        switch (Js.Nullable.toOption(jsProps##total)) {
        | None => 0
        | Some(i) => i
        },
      ~items=
        switch (Js.Nullable.toOption(jsProps##items)) {
        | None => []
        | Some(i) => i
        },
      ~error=Js.Nullable.toOption(jsProps##error),
      [||],
    )
  );
let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
inject(composedComponent, getInitialProps);
let default = withInitialProps(composedComponent);
