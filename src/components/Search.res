open Belt
open Webapi
open ReactNative

@module("latinize") external latinize: string => string = "default"

let cleanUp = s => s->latinize->Js.String2.replaceByRe(%re("/[^a-zA-Z0-9]+/g"), " ")

@react.component
let make = () => {
  let readHash = React.useCallback0(() =>
    Dom.window->Dom.Window.location->Dom.Location.hash->Js.String2.replace("#", "")->Utils.decodeURI
  )
  let (queryString, queryString_set) = React.useState(_ => readHash())
  React.useEffect1(() => {
    Dom.window->Dom.Window.location->Dom.Location.setHash(queryString)
    None
  }, [queryString])
  let handleChangeText = React.useCallback1(value => queryString_set(_ => value), [queryString_set])

  // sync hash with current state to avoid weird behavior
  React.useEffect3(() => {
    let timer = Js.Global.setInterval(() => {
      let qs = readHash()
      if qs != queryString {
        queryString_set(_ => qs)
      }
    }, 1000)
    Some(() => Js.Global.clearInterval(timer))
  }, (readHash, queryString, queryString_set))

  // debounce actual used query string so when user type, there is not one query per character typed
  let (usedQueryString, usedQueryString_set) = React.useState(_ => readHash())
  React.useEffect3(() => {
    let timer = Js.Global.setTimeout(() => {
      if queryString !== usedQueryString {
        usedQueryString_set(_ => queryString)
      }
    }, 250)
    Some(() => Js.Global.clearTimeout(timer))
  }, (queryString, usedQueryString, usedQueryString_set))

  let query = WPGraphQL.GetPostsFromSearch.use(
    WPGraphQL.GetPostsFromSearch.makeVariables(~first=100, ~search=usedQueryString->cleanUp, ()),
  )
  let queryTag = WPGraphQL.GetPostsFromTagSlug.use(
    WPGraphQL.GetPostsFromTagSlug.makeVariables(~first=100, ~search=usedQueryString, ()),
  )

  <>
    <View
      style={
        open Style
        style(~flexDirection=#row, ~flexShrink=1., ~justifyContent=#center, ())
      }>
      <TextInput
        style={
          open Style
          style(
            ~display=#flex,
            ~flexGrow=1.,
            ~flexShrink=1.,
            ~minWidth=0.->dp,
            ~maxWidth=300.->dp,
            ~margin=0.->dp,
            ~paddingVertical=Spacer.size(S)->dp,
            ~paddingHorizontal=Spacer.size(M)->dp,
            ~fontSize=22.,
            ~borderRadius=16.,
            ~borderWidth=StyleSheet.hairlineWidth,
            ~borderColor=Consts.Colors.main50,
            (),
          )
        }
        placeholder="Rechercher"
        placeholderTextColor=Consts.Colors.main
        value=queryString
        onChangeText={handleChangeText}
        clearButtonMode=#always
      />
    </View>
    {switch (query, queryTag) {
    | ({loading: true}, _)
    | (_, {loading: true}) =>
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
    | ({data: Some(response)}, {data: Some(responseTag)}) =>
      let posts = response.posts->Option.flatMap(p => p.nodes)->Option.getWithDefault([])
      let postsTag = responseTag.posts->Option.flatMap(p => p.nodes)->Option.getWithDefault([])
      let nodes =
        posts->Array.concat(
          postsTag->Array.keep(node =>
            node
            ->Option.map(pT =>
              !(
                posts
                ->Js.Array2.find(p =>
                  p->Option.map(p => p.id === pT.id)->Option.getWithDefault(false)
                )
                ->Option.isSome
              )
            )
            ->Option.getWithDefault(true)
          ),
        )
      <>
        <Next.Head> <title> {"Recherche"->React.string} </title> </Next.Head>
        {nodes->Array.length > 0 ? <PostList nodes /> : <Error label={Some(`Aucun résultat`)} />}
      </>
    | ({error: Some(error)}, _) => <Error label=Some(error.message) />
    | (_, {error: Some(error)}) => <Error label=Some(error.message) />
    | _ => <Error label=None />
    }}
  </>
}
