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
  ~onMouseEnter=?,
  ~onMouseLeave=?,
  ~style as styl: option<ReactNative.Style.t>=?,
) => {
  let router = Next.useRouter()
  let accessibilityRole = #link
  let style = Style.arrayOption([styl, isActive(href, router) ? activeStyle : None])
  href->Js.String2.startsWith("/")
    ? <Next.Link href>
        <View ?onMouseEnter ?onMouseLeave href ?accessibilityLabel accessibilityRole style>
          {children}
        </View>
      </Next.Link>
    : <View ?onMouseEnter ?onMouseLeave href ?accessibilityLabel accessibilityRole style>
        {children}
      </View>
}
