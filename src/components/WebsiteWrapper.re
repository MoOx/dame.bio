let component = ReasonReact.statelessComponent("WebsiteWrapper");

let make = children => {
  ...component,
  render: _ =>
    <>
      <GlobalMeta />
      <div className="device-small"> <HeaderSmall /> </div>
      <div className="device-large"> <HeaderLarge /> </div>
      <Container> ...children </Container>
      <Footer />
      <div
        className="device-small"
        style={ReactDOMRe.Style.unsafeAddProp(
          ReactDOMRe.Style.make(
            ~position="fixed",
            ~bottom="0",
            ~left="0",
            ~right="0",
            ~backgroundColor="#FDFFFFe6",
            (),
          ),
          "-webkit-backdrop-filter",
          "saturate(210%) blur(20px)",
        )}>
        <AppMenu />
      </div>
    </>,
};
