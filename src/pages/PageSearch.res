@react.component
let make = () => {
  let globals = WPGraphQL.useGlobals()
  let (mounted, mounted_set) = React.useState(_ => false)
  React.useEffect0(() => {
    mounted_set(_ => true)
    None
  })
  <AppWrapper ?globals>
    <ContainerMainContentLarge> {mounted ? <Search /> : React.null} </ContainerMainContentLarge>
    /* <SidebarSeparator /> */
    <Sidebar ?globals />
  </AppWrapper>
}

let default = make
