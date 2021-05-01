open ReactNative

let defaultIsActive = (href: string, router: Next.router) =>
  router.pathname === href || router.pathname ++ "/" === href

@react.component
let make = (
  ~accessibilityLabel: option<string>=?,
  ~activeStyle: option<ReactNative.Style.t>=?,
  ~children: React.element,
  ~href: string,
  ~isActive: (string, Next.router) => bool=defaultIsActive,
  ~rel: option<
    [
      | #alternate
      | #author
      | #bookmark
      | #external_
      | #help
      | #license
      | #next
      | #nofollow
      | #noopener
      | #noreferrer
      | #opener
      | #prev
      | #search
      | #tag
      | #ugc
      | #ugcNoFollow
    ],
  >=?,
  ~style as styl: option<ReactNative.Style.t>=?,
) => {
  let router = Next.useRouter()
  let accessibilityRole = #link
  let style = Style.arrayOption([styl, isActive(href, router) ? activeStyle : None])
  href->Js.String2.startsWith("/")
    ? <Next.Link href>
        <Text href ?rel ?accessibilityLabel accessibilityRole style> {children} </Text>
      </Next.Link>
    : <Text
        href
        ?accessibilityLabel
        accessibilityRole
        ?rel
        style
        onPress={_ => Linking.openURL(href)->ignore}>
        {children}
      </Text>
}
