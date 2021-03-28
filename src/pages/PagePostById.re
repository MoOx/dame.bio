// open Belt;
// open ReactNative;
// [@bs.module "@phenomic/preset-react-app/lib/client"]
// external withInitialProps: 'a => 'a = "withInitialProps";
// type status =
//   | Loading
//   | Ready
//   | Error(option(string));
// module GetPost = [%graphql
//   {|
//   query GetPost($databaseId: Int!){
//     posts(first: 1, where: {id: $databaseId, stati: DRAFT}) {
//       nodes {
//         ...WPGraphQL.Fragments.PostDetailFragment
//       }
//     }
//   }
// |}
// ];
// module GetPostQuery = ReasonApollo.CreateQuery(GetPost);
// [@react.component]
// let make = (~status, ~databaseId) => {
//   let itemQuery = GetPost.make(~databaseId, ());
//   <AppWrapper>
//     <ContainerMainContent>
//       {switch (status) {
//        | Loading => <LoadingIndicator />
//        | Error(error) => <Error label=error />
//        | Ready =>
//          <GetPostQuery variables=itemQuery##variables>
//            ...{({result}) =>
//              switch (result) {
//              | Loading => <LoadingIndicator />
//              | Error(error) => <Error label={Some(error.message)} />
//              | Data(response) =>
//                response##posts
//                ->Option.flatMap(p => p##nodes)
//                ->Option.map(nodes =>
//                    nodes
//                    ->Array.map(node =>
//                        node
//                        ->Option.map(item =>
//                            <View key=item.id>
//                              {item.title
//                               ->Option.mapWithDefault(React.null, title =>
//                                   <Next.Head
//                                     key=title
//                                     titleTemplate=Consts.titleTemplate>
//                                     <title> title->React.string </title>
//                                     <meta
//                                       name="description"
//                                       content={
//                                         item.content
//                                         ->Option.getWithDefault("")
//                                         ->Js.String.substrAtMost(
//                                             ~from=0,
//                                             ~length=120,
//                                           )
//                                         ++ "…"
//                                       }
//                                     />
//                                   </Next.Head>
//                                 )}
//                              <PostDetail item />
//                            </View>
//                          )
//                        ->Option.getWithDefault(React.null)
//                      )
//                    ->React.array
//                  )
//                ->Option.getWithDefault(
//                    <Error label={Some({j|Aucun résultat|j})} />,
//                  )
//              }
//            }
//          </GetPostQuery>
//        }}
//     </ContainerMainContent>
//   </AppWrapper>;
// };
// [@react.component]
// let composedComponent = (~status, ~error, ~params: {. "databaseId": int}) => {
//   React.createElementVariadic(
//     make,
//     makeProps(
//       ~status=
//         switch (status) {
//         | "loading" => Loading
//         | "ready" => Ready
//         | "error"
//         | _ => Error(Js.Nullable.toOption(error))
//         },
//       ~databaseId=params##databaseId,
//       (),
//     ),
//     [|React.null|],
//   );
// };
// /* let getInitialProps = (...args) => args; */
// /* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
//    inject(composedComponent, getInitialProps); */
// /* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
// let default =
//   withInitialProps(
//     WithApolloClient.make(
//       ~component=composedComponent,
//       ~initialOptions={"canRestoreInitialState": !Auth.isLogged()},
//     ),
//   );
