let component = ReasonReact.statelessComponent("RouteError");

let make = _ => {
  ...component,
  render: _ => {
    <AppWrapper>
      <ContainerMainContentLarge>
        <Error
          label={Some({j|Cette page est inaccessible ou n'existe pas!|j})}
        />
      </ContainerMainContentLarge>
      <Sidebar />
    </AppWrapper>;
  },
};

let default = ReasonReact.wrapReasonForJs(~component, _ => make([||]));
