open BsReactNative;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

let perPage = 8;

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItems = [%graphql
  {|
  query getItems($first: Int!, $categorySlug: String, $tagSlug: String, $cursorAfter: String){
    categories(first: 1, where: {slug: [$categorySlug]}) {
      nodes {
        id
        name
      }
    }
    posts(first: $first, after: $cursorAfter, where: {categoryName: $categorySlug, tag: $tagSlug}) {
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

let make = (~status, ~categorySlug, ~tagSlug, ~cursorAfter, _) => {
  ...component,
  render: _ => {
    let itemsQuery =
      GetItems.make(
        ~first=perPage,
        ~categorySlug?,
        ~tagSlug?,
        ~cursorAfter?,
        (),
      );
    <AppWrapper>
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
                 <>
                   {response##categories
                    ->Belt.Option.flatMap(p => p##nodes)
                    ->Belt.Option.mapWithDefault(ReasonReact.null, nodes =>
                        nodes
                        ->Belt.Array.map(node =>
                            node
                            ->Belt.Option.flatMap(node => node##name)
                            ->Belt.Option.mapWithDefault(
                                ReasonReact.null, title =>
                                <BsReactHelmet
                                  key=title titleTemplate=Consts.titleTemplate>
                                  <title> title->ReasonReact.string </title>
                                </BsReactHelmet>
                              )
                          )
                        ->ReasonReact.array
                      )}
                   {response##posts
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
                                       ++ tagSlug->Belt.Option.mapWithDefault(
                                            "", t =>
                                            "/tag/" ++ t
                                          )
                                       ++ "/after/"
                                       ++ cursor
                                       ++ "/"
                                     }>
                                     {j|Articles plus récents|j}
                                     ->ReasonReact.string
                                   </BannerButton>
                                 )
                               ->Belt.Option.getWithDefault(
                                   ReasonReact.null,
                                 ) :
                               ReasonReact.null}
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
                                       ++ tagSlug->Belt.Option.mapWithDefault(
                                            "", t =>
                                            "/tag/" ++ t
                                          )
                                       ++ "/after/"
                                       ++ cursor
                                       ++ "/"
                                     }>
                                     {j|Encore plus d'articles|j}
                                     ->ReasonReact.string
                                   </BannerButton>
                                 )
                               ->Belt.Option.getWithDefault(
                                   ReasonReact.null,
                                 ) :
                               ReasonReact.null}
                          </View>
                        </>
                      )
                    ->Belt.Option.getWithDefault(
                        <Error label={Some({j|Aucun résultat|j})} />,
                      )}
                 </>;
               }
             }
           </GetItemsQuery>
         }}
      </ContainerMainContentLarge>
      /* <SidebarSeparator /> */
      <Sidebar />
    </AppWrapper>;
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
      ~tagSlug=Js.Nullable.toOption(jsProps##params##tagSlug),
      ~cursorAfter=Js.Nullable.toOption(jsProps##params##cursorAfter),
      [||],
    )
  );

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
