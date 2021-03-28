open Belt

@react.component
let make = () => {
  let globals = WPGraphQL.useGlobals()
  let query = WPGraphQL.GetPage.use(WPGraphQL.GetPage.makeVariables(~pageSlug="contact", ()))
  <AppWrapper ?globals>
    <ContainerMainContentLarge>
      {switch query {
      | {loading: true} => <LoadingIndicator />
      | {data: Some(response)} => <>
          {response.pages
          ->Option.flatMap(p => p.nodes)
          ->Option.map(nodes =>
            nodes
            ->Array.map(node =>
              node
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
                  <ContactForm page=item />
                </React.Fragment>
              )
              ->Option.getWithDefault(<ContactForm />)
            )
            ->React.array
          )
          ->Option.getWithDefault(<Error label={Some(j`Aucun résultat`)} />)}
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
