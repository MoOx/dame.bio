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

[@react.component]
let make = (~status, ()) => {
  let itemsQuery = GetItems.make(~pageSlug="contact", ());
  <AppWrapper>
    <ContainerMainContentLarge key="contact">
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
};

[@react.component]
let composedComponent = (~status, ~error) =>
  React.createElementVariadic(
    make,
    makeProps(
      ~status=
        switch (status) {
        | "loading" => Loading
        | "ready" => Ready
        | "error"
        | _ => Error(Js.Nullable.toOption(error))
        },
      (),
    ),
    [|React.null|],
  );

let default = withInitialProps(WithApolloClient.make(composedComponent));
