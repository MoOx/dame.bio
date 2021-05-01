open Belt

let perPageForHome = 10
let perPage = 250

@react.component
let make = (~pageOrCategorySlug, ()) => {
  let globals = WPGraphQL.useGlobals()
  let query = WPGraphQL.GetPageAndPostsFromSlug.use(
    WPGraphQL.GetPageAndPostsFromSlug.makeVariables(
      ~pageSlug=pageOrCategorySlug->Option.getWithDefault("noop"),
      ~categorySlug=pageOrCategorySlug->Option.getWithDefault(""),
      ~first=pageOrCategorySlug->Option.isNone ? perPageForHome : perPage,
      (),
    ),
  )
  <AppWrapper ?globals>
    <ContainerMainContentLarge>
      {switch query {
      | {loading: true} =>
        <PostList
          nodes=[
            Some(WPGraphQL.Placeholders.postPreview(1)),
            Some(WPGraphQL.Placeholders.postPreview(2)),
            Some(WPGraphQL.Placeholders.postPreview(3)),
            Some(WPGraphQL.Placeholders.postPreview(4)),
            Some(WPGraphQL.Placeholders.postPreview(5)),
            Some(WPGraphQL.Placeholders.postPreview(6)),
            Some(WPGraphQL.Placeholders.postPreview(7)),
            Some(WPGraphQL.Placeholders.postPreview(8)),
          ]
        />
      | {data: Some(response)} =>
        let hasPosts =
          response.posts
          ->Option.flatMap(p => p.nodes)
          ->Option.map(nodes => nodes->Array.length > 0)
          ->Option.getWithDefault(false)
        let page =
          response.pages
          ->Option.flatMap(p => p.nodes)
          ->Option.flatMap(nodes => nodes[0])
          ->Option.flatMap(node => node)
        let hasPage = page->Option.mapWithDefault(false, _ => true)
        <>
          <CategoryOrHomeTitle
            categories=response.categories
            generalSettings={globals->Option.flatMap(globals => globals.generalSettings)}
          />
          {page->Option.map(item => <PageDetail item />)->Option.getWithDefault(React.null)}
          {response.posts
          ->Option.flatMap(p => p.nodes)
          ->Option.map(nodes => <PostList nodes />)
          ->Option.getWithDefault(React.null)}
          {!hasPage && !hasPosts ? <Error label={Some(`Aucun résultat`)} /> : React.null}
        </>
      | {error: Some(error)} => <Error label=Some(error.message) />
      | _ => <Error label=None />
      }}
    </ContainerMainContentLarge>
    /* <SidebarSeparator /> */
    <Sidebar ?globals />
  </AppWrapper>
}

let default = make
