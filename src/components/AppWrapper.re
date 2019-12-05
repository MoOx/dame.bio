[@react.component]
let make = (~children) =>
  <>
    <AppMeta />
    <HeaderWithRouter />
    <Container> children </Container>
    <Footer />
    <div
      className="device-small menu-backdrop"
      style={ReactDOMRe.Style.make(
        ~position="fixed",
        ~bottom="0",
        ~left="0",
        ~right="0",
        (),
      )}>
      <TabBarWithRouter />
    </div>
  </>;
