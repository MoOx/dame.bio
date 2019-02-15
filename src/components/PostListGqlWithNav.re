open Belt;
open BsReactNative;

let component = ReasonReact.statelessComponent("PostListGqlWithNav");

let make = (~posts, ~categorySlug, ~tagSlug, _) => {
  ...component,
  render: _self => {
    let pageInfo = posts->Option.flatMap(p => p##pageInfo);
    <>
      {posts
       ->Option.flatMap(p => p##edges)
       ->Option.map(edges =>
           <>
             <PostListFromGraphQLQuery edges />
             <View
               style=Style.(
                 style([flexDirection(Row), justifyContent(SpaceAround)])
               )>
               {// https://github.com/wp-graphql/wp-graphql/issues/594
                // not working yet
                pageInfo
                ->Option.map(p => p##hasPreviousPage)
                ->Option.getWithDefault(false) ?
                  pageInfo
                  ->Option.flatMap(p => p##startCursor)
                  ->Option.map(cursor =>
                      <BannerButton
                        href={
                          categorySlug->Option.mapWithDefault("", c =>
                            "/" ++ c
                          )
                          ++ tagSlug->Option.mapWithDefault("", t =>
                               "/tag/" ++ t
                             )
                          ++ "/after/"
                          ++ cursor
                          ++ "/"
                        }>
                        {j|Articles plus récents|j}->ReasonReact.string
                      </BannerButton>
                    )
                  ->Option.getWithDefault(ReasonReact.null) :
                  ReasonReact.null}
               {pageInfo
                ->Option.map(p => p##hasNextPage)
                ->Option.getWithDefault(false) ?
                  pageInfo
                  ->Option.flatMap(p => p##endCursor)
                  ->Option.map(cursor =>
                      <BannerButton
                        href={
                          categorySlug->Option.mapWithDefault("", c =>
                            "/" ++ c
                          )
                          ++ tagSlug->Option.mapWithDefault("", t =>
                               "/tag/" ++ t
                             )
                          ++ "/after/"
                          ++ cursor
                          ++ "/"
                        }>
                        {j|Encore plus d'articles|j}->ReasonReact.string
                      </BannerButton>
                    )
                  ->Option.getWithDefault(ReasonReact.null) :
                  ReasonReact.null}
             </View>
           </>
         )
       ->Option.getWithDefault(<Error label={Some({j|Aucun résultat|j})} />)}
    </>;
  },
};
