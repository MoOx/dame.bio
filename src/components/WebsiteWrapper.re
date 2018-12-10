let component = ReasonReact.statelessComponent("WebsiteWrapper");

let make = children => {
  ...component,
  render: _ =>
    <>
      <CommonThings />
      <Header />
      <Container> ...children </Container>
      <Footer />
    </>,
};
