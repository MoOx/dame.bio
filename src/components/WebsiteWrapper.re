let component = ReasonReact.statelessComponent("WebsiteWrapper");

let make = children => {
  ...component,
  render: _ =>
    <>
      <CommonThings />
      <Header />
      <Container> <MainContent> ...children </MainContent> </Container>
      <Footer />
    </>,
};
