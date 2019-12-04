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
      nodes {
        id
        title(format: RAW)
        slug
        dateGmt
        content
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
                  ->Option.flatMap(p => p##nodes)
                  ->Option.flatMap(nodes => nodes[0])
                  ->Option.flatMap(node => node)
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
