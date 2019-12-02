open Belt;
open BsReactNative;

[@bs.module "@phenomic/preset-react-app/lib/client"]
external withInitialProps: 'a => 'a = "";

type status =
  | Loading
  | Ready
  | Error(option(string));

module Fragments = [%graphql
  {|
  fragment CommentFragment on Comment {
    commentId
    parent {
      commentId
    }
    dateGmt
    content
    author {
      ... on User {
        userId
        name
        url
        email
      }
      ... on CommentAuthor {
        name
        url
        email
      }
    }
  }
|}
];

module GetItem = [%graphql
  {|
  query getItem($postId: Int!){
    posts(first: 1, where: {id: $postId, stati: DRAFT}) {
      edges {
        node {
          id
          title(format: RAW)
          slug
          commentCount
          likeCount
          postId
          dateGmt
          content
          comments(
            first: 1000,
            where: {
              parent: 99999,
              orderby: COMMENT_DATE_GMT,
              order: ASC
            }
          ) {
          # 99999 is a trick defined in `graphql_comment_connection_query_args` filter to have all comments
            nodes {
              ...Fragments.CommentFragment
            }
          }
          categories {
            nodes {
              name
              slug
              parent {
                id
              }
            }
          }
          tags(first: 100) {
            nodes {
              name
              slug
            }
          }
        }
      }
    }
  }
|}
];

module GetItemQuery = ReasonApollo.CreateQuery(GetItem);

[@react.component]
let make = (~status, ~postId) => {
  let itemQuery = GetItem.make(~postId, ());
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
               ->Option.flatMap(p => p##edges)
               ->Option.map(edges =>
                   edges
                   ->Array.map(edge =>
                       edge
                       ->Option.flatMap(edge => edge##node)
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
let composedComponent = (~status, ~error, ~params: {. "postId": int}) => {
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
      ~postId=params##postId,
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
