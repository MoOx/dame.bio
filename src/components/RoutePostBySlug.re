open Belt;
open BsReactNative;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

type status =
  | Loading
  | Ready
  | Error(option(string));

module GetItem = [%graphql
  {|
  query getItem($postSlug: String!){
    posts(first: 1, where: {name: $postSlug}) {
      nodes {
        ...WPGraphQL.Fragments.PostDetailFragment
      }
    }
  }
|}
];

module GetItemQuery = ReasonApollo.CreateQuery(GetItem);

[@react.component]
let make = (~status, ~postSlug) => {
  let itemQuery = GetItem.make(~postSlug, ());
  <AppWrapper>
    <ContainerMainContent>
      {switch (status) {
       | Loading => <LoadingIndicator />
       | Error(error) => <Error label=error />
       | Ready =>
         <GetItemQuery variables=itemQuery##variables>
           ...{({result}) =>
             switch (result) {
             | Loading => <LoadingIndicator />
             | Error(error) => <Error label={Some(error##message)} />
             | Data(response) =>
               response##posts
               ->Option.flatMap(p => p##nodes)
               ->Option.map(nodes =>
                   nodes
                   ->Array.map(node =>
                       node
                       ->Option.map(item =>
                           <View key=item##id>
                             {item##title
                              ->Option.mapWithDefault(React.null, title =>
                                  <BsReactHelmet
                                    key=title
                                    titleTemplate=Consts.titleTemplate>
                                    <title> title->React.string </title>
                                  </BsReactHelmet>
                                )}
                             <PostDetail item />
                           </View>
                         )
                       ->Option.getWithDefault(React.null)
                     )
                   ->React.array
                 )
               ->Option.getWithDefault(
                   <Error label={Some({j|Aucun résultat|j})} />,
                 )
             }
           }
         </GetItemQuery>
       }}
    </ContainerMainContent>
  </AppWrapper>;
};

[@react.component]
let composedComponent = (~status, ~error, ~params: {. "postSlug": string}) => {
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
      ~postSlug=params##postSlug,
      (),
    ),
    [|React.null|],
  );
};

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
