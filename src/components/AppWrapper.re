[@react.component]
let make = (~globals=?, ~children) => {
  let currentLocation = Next.useRouter().asPath;
  <>
    <AppMeta />
    <Header ?globals currentLocation />
    <Container> children </Container>
    <Footer ?globals currentLocation />
    <div
      className="device-small menu-backdrop"
      style={ReactDOMRe.Style.make(
        ~position="fixed",
        ~bottom="0",
        ~left="0",
        ~right="0",
        (),
      )}>
      <TabBar ?globals />
    </div>
  </>;
};
