open Belt

type renderItem = (~url: string, ~label: string, ~isActive: bool) => React.element

let getMenu = (globals: option<WPGraphQL.GetGlobals.GetGlobals_inner.t>, id) => {
  globals
  ->Option.flatMap(globals => globals.menus)
  ->Option.flatMap(menus => menus.nodes)
  ->Option.map(nodes => nodes->Array.keepMap(node => node))
  ->Option.flatMap(nodes => (nodes->Array.keep(node => node.id === id))[0])
}

@react.component
let make = (
  ~menu: option<WPGraphQL.GetGlobals.GetGlobals_inner.t_menus_nodes>=?,
  ~currentLocation,
  ~renderItem,
  ~maxItems=100,
) => {
  menu
  ->Option.flatMap(cs =>
    cs.menuItems->Option.flatMap(maybeItems =>
      maybeItems.nodes->Option.map(items =>
        items
        ->Array.mapWithIndex((index, maybeItem) =>
          maybeItem
          ->Option.flatMap(item =>
            item.label->Option.flatMap(label =>
              item.url->Option.map(url => {
                let cleanUrl =
                  url
                  ->Js.String2.replace(Consts.backendUrl, "")
                  ->Js.String2.replace("/category/", "/")
                  ->Js.String2.replaceByRe(%re("/\/$/"), "")

                let isActive = currentLocation->Js.String2.startsWith(cleanUrl)
                renderItem(~index, ~url=cleanUrl, ~label, ~isActive)
              })
            )
          )
          ->Option.getWithDefault(React.null)
        )
        ->Array.slice(~offset=0, ~len=maxItems)
        ->React.array
      )
    )
  )
  ->Option.getWithDefault(React.null)
}
