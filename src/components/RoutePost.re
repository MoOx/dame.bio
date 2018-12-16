open Helpers;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItem = [%graphql
  {|
  query getItem($slug: String!){
    posts(first: 1, where: {name: $slug}) {
      edges {
        node {
          id
          title
          slug
          commentCount
          likeCount
          postId
          content
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

module GetItemQuery = ReasonApollo.CreateQuery(GetItem);

let component = ReasonReact.statelessComponent("RoutePost");

let make = (~status, ~slug, _) => {
  ...component,
  render: _ => {
    let itemQuery = GetItem.make(~slug, ());
    <WebsiteWrapper>
      <ContainerMainContent>
        {switch (status) {
         | Loading => <LoadingIndicator />
         | Error(error) => <Error label=error />
         | Ready =>
           <GetItemQuery variables=itemQuery##variables>
             ...{({result}) =>
               switch (result) {
               | Loading => <LoadingIndicator />
               | Error(error) => <Error label={Some(error##message)} />
               | Data(response) =>
                 response##posts
                 ->Belt.Option.flatMap(p => p##edges)
                 ->Belt.Option.map(edges =>
                     edges
                     ->Belt.Array.map(edge =>
                         edge
                         ->Belt.Option.flatMap(edge => edge##node)
                         ->Belt.Option.map(item =>
                             <PostDetail key=item##id item />
                           )
                         ->Belt.Option.getWithDefault(nothing)
                       )
                     ->ReasonReact.array
                   )
                 ->Belt.Option.getWithDefault(
                     <Error label={Some({j|Aucun résultat|j})} />,
                   )
               }
             }
           </GetItemQuery>
         }}
      </ContainerMainContent>
    </WebsiteWrapper>;
  },
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
      ~slug=jsProps##params##splat,
      [||],
    )
  );

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
