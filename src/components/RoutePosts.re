open BsReactNative;

open Helpers;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

let per_page = 8;

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItems = [%graphql
  {|
  query getItems($categoryName: String, $after: String){
    posts(first: 8, after: $after, where: {categoryName: $categoryName}) {
      edges {
        node {
          id
          title
          slug
          featuredImage {
            mediaDetails {
              sizes {
                name
                sourceUrl
              }
            }
          }
          dateGmt
          commentCount
          categories {
            nodes {
              name
              slug
              parent {
                id
              }
            }
          }
          tags {
            nodes {
              name
              slug
            }
          }
        }
      }
    }
  }
|}
];

module GetItemsQuery = ReasonApollo.CreateQuery(GetItems);

let component = ReasonReact.statelessComponent("RoutePosts");

let make = (~status, _) => {
  ...component,
  render: _ =>
    <WebsiteWrapper>
      {
        switch (status) {
        | Loading => <LoadingIndicator />
        | Error(error) => <Error label=error />
        | Ready =>
          <GetItemsQuery>
            ...(
                 ({result}) =>
                   switch (result) {
                   | Loading => <LoadingIndicator />
                   | Error(error) => <Error label={Some(error##message)} />
                   | Data(response) =>
                     switch ([%get_in response##posts#??edges]) {
                     | None => <Error label={Some({j|Aucun résultat|j})} />
                     | Some(items) => <PostList items />
                     }
                   }
               )
          </GetItemsQuery>
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
        | _ => Error(Js.Nullable.toOption(jsProps##error))
        },
      [||],
    )
  );

/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

let default = withInitialProps(WithApolloClient.make(composedComponent));
