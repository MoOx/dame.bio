open Belt

@react.component
let make = (~postId) => {
  let globals = WPGraphQL.useGlobals()
  let query = WPGraphQL.GetPostById.use(WPGraphQL.GetPostById.makeVariables(~postId, ()))
  <AppWrapper ?globals>
    <ContainerMainContentLarge>
      {switch query {
      | {loading: true} => <LoadingIndicator />
      | {data: Some(response)} =>
        response.post
        ->Option.map(item =>
          <React.Fragment key=item.id>
            {item.title->Option.mapWithDefault(React.null, title =>
              <Next.Head key=title>
                <title> {title->React.string} </title>
                // <link rel="canonical" href={Consts.frontendUrl ++ item->Utils.postHref} />
                <meta
                  name="description"
                  content={item.content
                  ->Option.getWithDefault("")
                  ->Js.String.substrAtMost(~from=0, ~length=120) ++ "…"}
                />
              </Next.Head>
            )}
            <PostDetail item />
          </React.Fragment>
        )
        ->Option.getWithDefault(<Error label={Some(j`Aucun résultat`)} />)
      | {error: Some(error)} => <Error label=Some(error.message) />
      | _ => <Error label=None />
      }}
    </ContainerMainContentLarge>
    /* <SidebarSeparator /> */
    <Sidebar ?globals />
  </AppWrapper>
}

let default = make
