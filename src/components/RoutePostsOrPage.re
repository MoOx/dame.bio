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
      nodes {
        ...WPGraphQL.Fragments.PostPreviewFragment
      }
    }
    pages(first: 1, where: {name: $pageSlug}) {
      nodes {
        id
        title(format: RAW)
        slug
        dateGmt
        content
      }
    }
  }
|}
];

/* let getAllPossibleUrls = (args) => {
     Js.log2("args", args);
   } */

module GetItemsQuery = ReasonApollo.CreateQuery(GetItems);

[@react.component]
let make = (~status, ~categoryOrPageSlug, ~tagSlug, ~cursorAfter, ()) => {
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
               let hasPosts =
                 response##posts
                 ->Option.flatMap(p => p##nodes)
                 ->Option.map(nodes => nodes->Array.length > 0)
                 ->Option.getWithDefault(false);
               let page =
                 response##pages
                 ->Option.flatMap(p => p##nodes)
                 ->Option.flatMap(nodes => nodes[0])
                 ->Option.flatMap(node => node);
               let hasPage = page->Option.mapWithDefault(false, _ => true);
               <>
                 <CategoryOrHomeTitle
                   categories=response##categories
                   generalSettings=response##generalSettings
                 />
                 {page
                  ->Option.map(item => <PageDetail item />)
                  ->Option.getWithDefault(React.null)}
                 {hasPosts
                    ? <PostListWithNav
                        posts=response##posts
                        categorySlug=categoryOrPageSlug
                        tagSlug
                        cursorAfter
                      />
                    : React.null}
                 {!hasPage && !hasPosts
                    ? <Error label={Some({j|Aucun résultat|j})} />
                    : React.null}
               </>;
             }
           }
         </GetItemsQuery>
       }}
    </ContainerMainContentLarge>
    /* <SidebarSeparator /> */
    <Sidebar />
  </AppWrapper>;
};

[@react.component]
let composedComponent =
    (
      ~status,
      ~error,
      ~params: {
         .
         "categoryOrPageSlug": option(string),
         "tagSlug": option(string),
         "cursorAfter": option(string),
       },
    ) =>
  React.createElementVariadic(
    make,
    makeProps(
      ~status=
        switch (status) {
        | "loading" => Loading
        | "ready" => Ready
        | "error"
        | _ => Error(Js.Nullable.toOption(error))
        },
      ~categoryOrPageSlug=params##categoryOrPageSlug,
      ~tagSlug=params##tagSlug,
      ~cursorAfter=params##cursorAfter,
      (),
    ),
    [|React.null|],
  );

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
