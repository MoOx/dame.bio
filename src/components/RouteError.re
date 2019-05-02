let component = ReasonReact.statelessComponent("RouteError");

[@react.component]
let make = () =>
  <AppWrapper>
    <ContainerMainContentLarge>
      <Error
        label={Some({j|Cette page est inaccessible ou n'existe pas!|j})}
      />
    </ContainerMainContentLarge>
    <Sidebar />
  </AppWrapper>;

let default = make;
