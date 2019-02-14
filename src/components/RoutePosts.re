open Belt;
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
    generalSettings {
      title
      description
    }
    categories(first: 1, where: {slug: [$categorySlug]}) {
      nodes {
        id
        name
        description
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
                   response##posts->Option.flatMap(p => p##pageInfo);
                 <>
                   {response##categories
                    ->Option.flatMap(p => p##nodes)
                    ->Option.flatMap(nodes => nodes[0])
                    ->Option.flatMap(node => node)
                    ->Option.flatMap(node =>
                        node##description->Option.isSome ?
                          node##description :
                          node##name->Option.isSome ? node##name : None
                      )
                    ->Option.map(title =>
                        <BsReactHelmet titleTemplate=Consts.titleTemplate>
                          <title> title->ReasonReact.string </title>
                        </BsReactHelmet>
                      )
                    ->Option.getWithDefault(
                        response##generalSettings
                        ->Option.flatMap(node => node##description)
                        ->Option.map(title =>
                            <BsReactHelmet
                              titleTemplate=Consts.titleTemplateHome>
                              <title> title->ReasonReact.string </title>
                            </BsReactHelmet>
                          )
                        ->Option.getWithDefault(ReasonReact.null),
                      )}
                   {response##posts
                    ->Option.flatMap(p => p##edges)
                    ->Option.map(edges =>
                        <>
                          <PostListFromGraphQLQuery edges />
                          <View
                            style=Style.(
                              style([
                                flexDirection(Row),
                                justifyContent(SpaceAround),
                              ])
                            )>
                            {// not working yet
                             // https://github.com/wp-graphql/wp-graphql/issues/594
                             pageInfo
                             ->Option.map(p => p##hasPreviousPage)
                             ->Option.getWithDefault(false) ?
                               pageInfo
                               ->Option.flatMap(p => p##startCursor)
                               ->Option.map(cursor =>
                                   <BannerButton
                                     href={
                                       categorySlug->Option.mapWithDefault(
                                         "", c =>
                                         "/" ++ c
                                       )
                                       ++ tagSlug->Option.mapWithDefault("", t =>
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
                               ->Option.getWithDefault(ReasonReact.null) :
                               ReasonReact.null}
                            {pageInfo
                             ->Option.map(p => p##hasNextPage)
                             ->Option.getWithDefault(false) ?
                               pageInfo
                               ->Option.flatMap(p => p##endCursor)
                               ->Option.map(cursor =>
                                   <BannerButton
                                     href={
                                       categorySlug->Option.mapWithDefault(
                                         "", c =>
                                         "/" ++ c
                                       )
                                       ++ tagSlug->Option.mapWithDefault("", t =>
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
                               ->Option.getWithDefault(ReasonReact.null) :
                               ReasonReact.null}
                          </View>
                        </>
                      )
                    ->Option.getWithDefault(
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
