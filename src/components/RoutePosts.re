open BsReactNative;
open Helpers;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

let perPage = 8;

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItems = [%graphql
  {|
  query getItems($first: Int!, $categorySlug: String, $cursorAfter: String){
    posts(first: $first, after: $cursorAfter, where: {categoryName: $categorySlug}) {
      pageInfo {
        startCursor
        endCursor
        hasNextPage
        hasPreviousPage
      }
      edges {
        node {
          id
          title
          slug
          dateGmt
          commentCount
          likeCount
          featuredImage {
            mediaDetails {
              sizes {
                name
                sourceUrl
              }
            }
          }
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

/* let getAllPossibleUrls = (args) => {
     Js.log2("args", args);
   } */

module GetItemsQuery = ReasonApollo.CreateQuery(GetItems);

let component = ReasonReact.statelessComponent("RoutePosts");

let make = (~status, ~categorySlug, ~cursorAfter, _) => {
  ...component,
  render: _ => {
    let itemsQuery =
      GetItems.make(~first=perPage, ~categorySlug?, ~cursorAfter?, ());
    <WebsiteWrapper>
      <ContainerMainContentLarge>
        {switch (status) {
         | Loading => <LoadingIndicator />
         | Error(error) => <Error label=error />
         | Ready =>
           <GetItemsQuery variables=itemsQuery##variables>
             ...{({result}) =>
               switch (result) {
               | Loading => <LoadingIndicator />
               | Error(error) => <Error label={Some(error##message)} />
               | Data(response) =>
                 let pageInfo =
                   response##posts->Belt.Option.flatMap(p => p##pageInfo);
                 response##posts
                 ->Belt.Option.flatMap(p => p##edges)
                 ->Belt.Option.map(edges =>
                     <>
                       <PostListFromGraphQLQuery edges />
                       <View
                         style=Style.(
                           style([
                             flexDirection(Row),
                             justifyContent(SpaceAround),
                           ])
                         )>
                         {/* not working yet
                             https://github.com/wp-graphql/wp-graphql/issues/594 */
                          pageInfo
                          ->Belt.Option.map(p => p##hasPreviousPage)
                          ->Belt.Option.getWithDefault(false) ?
                            pageInfo
                            ->Belt.Option.flatMap(p => p##startCursor)
                            ->Belt.Option.map(cursor =>
                                <BannerButton
                                  href={
                                    categorySlug->Belt.Option.mapWithDefault(
                                      "", c =>
                                      "/" ++ c
                                    )
                                    ++ "/after/"
                                    ++ cursor
                                    ++ "/"
                                  }>
                                  {{j|Articles plus récents|j} |> text}
                                </BannerButton>
                              )
                            ->Belt.Option.getWithDefault(nothing) :
                            nothing}
                         {pageInfo
                          ->Belt.Option.map(p => p##hasNextPage)
                          ->Belt.Option.getWithDefault(false) ?
                            pageInfo
                            ->Belt.Option.flatMap(p => p##endCursor)
                            ->Belt.Option.map(cursor =>
                                <BannerButton
                                  href={
                                    categorySlug->Belt.Option.mapWithDefault(
                                      "", c =>
                                      "/" ++ c
                                    )
                                    ++ "/after/"
                                    ++ cursor
                                    ++ "/"
                                  }>
                                  {{j|Encore plus d'articles|j} |> text}
                                </BannerButton>
                              )
                            ->Belt.Option.getWithDefault(nothing) :
                            nothing}
                       </View>
                     </>
                   )
                 ->Belt.Option.getWithDefault(
                     <Error label={Some({j|Aucun résultat|j})} />,
                   );
               }
             }
           </GetItemsQuery>
         }}
      </ContainerMainContentLarge>
      /* <SidebarSeparator /> */
      <Sidebar />
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
      ~categorySlug=Js.Nullable.toOption(jsProps##params##categorySlug),
      ~cursorAfter=Js.Nullable.toOption(jsProps##params##cursorAfter),
      [||],
    )
  );

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
