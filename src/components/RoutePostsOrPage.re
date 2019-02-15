open Belt;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

let perPage = 8;

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItems = [%graphql
  {|
  query getItems($first: Int!, $pageSlug: String, $categorySlug: String, $tagSlug: String, $cursorAfter: String){
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
    pages(first: 1, where: {name: $pageSlug}) {
      edges {
        node {
          id
          title(format: RAW)
          slug
          dateGmt
          content
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

let component = ReasonReact.statelessComponent("RoutePostsOrPage");

let make = (~status, ~categoryOrPageSlug, ~tagSlug, ~cursorAfter, _) => {
  ...component,
  render: _ => {
    let itemsQuery =
      GetItems.make(
        ~first=perPage,
        ~pageSlug=categoryOrPageSlug->Option.getWithDefault("noop"),
        ~categorySlug=categoryOrPageSlug->Option.getWithDefault(""),
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
                 let hasPosts = response##posts->Utils.hasEdges;
                 let page =
                   response##pages
                   ->Option.flatMap(p => p##edges)
                   ->Option.flatMap(edges => edges[0])
                   ->Option.flatMap(edge => edge)
                   ->Option.flatMap(edge => edge##node);
                 let hasPage = page->Option.mapWithDefault(false, _ => true);
                 <>
                   <CategoryOrHomeTitle
                     categories=response##categories
                     generalSettings=response##generalSettings
                   />
                   {page
                    ->Option.map(item => <PageDetail item />)
                    ->Option.getWithDefault(ReasonReact.null)}
                   {hasPosts ?
                      <PostListGqlWithNav
                        posts=response##posts
                        categorySlug=categoryOrPageSlug
                        tagSlug
                      /> :
                      ReasonReact.null}
                   {!hasPage && !hasPosts ?
                      <Error label={Some({j|Aucun résultat|j})} /> :
                      ReasonReact.null}
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
      ~categoryOrPageSlug=
        Js.Nullable.toOption(jsProps##params##categoryOrPageSlug),
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
