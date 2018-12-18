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
  query getItem($postSlug: String!){
    posts(first: 1, where: {name: $postSlug}) {
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

let component = ReasonReact.statelessComponent("RoutePost");

let make = (~status, ~postSlug, _) => {
  ...component,
  render: _ => {
    let itemQuery = GetItem.make(~postSlug, ());
    <WebsiteWrapper>
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
                 ->Belt.Option.flatMap(p => p##edges)
                 ->Belt.Option.map(edges =>
                     edges
                     ->Belt.Array.map(edge =>
                         edge
                         ->Belt.Option.flatMap(edge => edge##node)
                         ->Belt.Option.map(item =>
                             <View key=item##id>
                               {item##title
                                ->Belt.Option.mapWithDefault(
                                    ReasonReact.null, title =>
                                    <BsReactHelmet
                                      key=title
                                      titleTemplate=Consts.titleTemplate>
                                      <title>
                                        title->ReasonReact.string
                                      </title>
                                    </BsReactHelmet>
                                  )}
                               <PostDetail item />
                             </View>
                           )
                         ->Belt.Option.getWithDefault(ReasonReact.null)
                       )
                     ->ReasonReact.array
                   )
                 ->Belt.Option.getWithDefault(
                     <Error label={Some({j|Aucun résultat|j})} />,
                   )
               }
             }
           </GetItemQuery>
         }}
      </ContainerMainContent>
    </WebsiteWrapper>;
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
      ~postSlug=jsProps##params##splat,
      [||],
    )
  );

/* let getInitialProps = (...args) => args; */
/* let inject = [%bs.raw {| (cls, fn) => cls.getInitialProps = fn |}];
   inject(composedComponent, getInitialProps); */

/* let default = withInitialProps(WithApolloClient.make(composedComponent), getAllPossibleUrls); */
let default = withInitialProps(WithApolloClient.make(composedComponent));
