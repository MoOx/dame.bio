let component = ReasonReact.statelessComponent("AppWrapper");

let make = children => {
  ...component,
  render: _ =>
    <>
      <AppMeta />
      <div className="device-small"> <HeaderSmall /> </div>
      <div className="device-large"> <HeaderLarge /> </div>
      <Container> ...children </Container>
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
        <AppMenuWithRouter />
      </div>
    </>,
};
