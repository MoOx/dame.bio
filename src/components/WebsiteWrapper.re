let component = ReasonReact.statelessComponent("WebsiteWrapper");

let make = children => {
  ...component,
  render: _ =>
    <>
      <GlobalMeta />
      <Header />
      <Container> ...children </Container>
      <Footer />
    </>,
};
