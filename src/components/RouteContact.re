open Belt;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItems = [%graphql
  {|
  query getItems($pageSlug: String){
    pages(first: 1, where: {name: $pageSlug}) {
      edges {
        node {
          id
          title(format: RAW)
          slug
          dateGmt
          content
        }
      }
    }
  }
|}
];

module GetItemsQuery = ReasonApollo.CreateQuery(GetItems);

let component = ReasonReact.statelessComponent("RouteContact");

let make = (~status, _) => {
  ...component,
  render: _ => {
    let itemsQuery = GetItems.make(~pageSlug="contact", ());
    <AppWrapper>
      <ContainerMainContentLarge>
        {switch (status) {
         | Loading => <LoadingIndicator />
         | Error(error) => <Error label=error />
         | Ready =>
           <GetItemsQuery variables=itemsQuery##variables>
             ...{({result}) =>
               switch (result) {
               | Loading => <LoadingIndicator />
               | Error(error) => <Error label={Some(error##message)} />
               | Data(response) =>
                 <>
                   {response##pages
                    ->Option.flatMap(p => p##edges)
                    ->Option.flatMap(edges => edges[0])
                    ->Option.flatMap(edge => edge)
                    ->Option.flatMap(edge => edge##node)
                    ->Option.map(item => <ContactForm page=item />)
                    ->Option.getWithDefault(<ContactForm />)}
                 </>
               }
             }
           </GetItemsQuery>
         }}
      </ContainerMainContentLarge>
      /* <SidebarSeparator /> */
      <Sidebar />
    </AppWrapper>;
  },
};

let composedComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~status=
        switch (jsProps##status) {
        | "loading" => Loading
        | "ready" => Ready
        | "error"
        | _ => Error(Js.Nullable.toOption(jsProps##error))
        },
      [||],
    )
  );

let default = withInitialProps(WithApolloClient.make(composedComponent));
