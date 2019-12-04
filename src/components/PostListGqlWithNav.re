open Belt;
open BsReactNative;

[@react.component]
let make = (~posts, ~categorySlug, ~tagSlug, ~cursorAfter, ()) => {
  let pageInfo = posts->Option.flatMap(p => p##pageInfo);
  <>
    {posts
     ->Option.flatMap(p => p##nodes)
     ->Option.map(nodes =>
         <>
           <PostListFromGraphQLQuery nodes />
           <View
             style=Style.(
               style([flexDirection(Row), justifyContent(SpaceAround)])
             )>
             {// https://github.com/wp-graphql/wp-graphql/issues/594
              // not working yet
              pageInfo
              ->Option.map(p => p##hasPreviousPage)
              ->Option.getWithDefault(false)
                ? pageInfo
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
                        {j|Articles plus récents|j}->React.string
                      </BannerButton>
                    )
                  ->Option.getWithDefault(React.null)
                : cursorAfter->Option.isSome
                    ? <BannerButton href="javascript:history.go(-1)">
                        {j|Articles plus récents|j}->React.string
                      </BannerButton>
                    : React.null}
             {pageInfo
              ->Option.map(p => p##hasNextPage)
              ->Option.getWithDefault(false)
                ? pageInfo
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
                        {j|Encore plus d'articles|j}->React.string
                      </BannerButton>
                    )
                  ->Option.getWithDefault(React.null)
                : React.null}
           </View>
         </>
       )
     ->Option.getWithDefault(<Error label={Some({j|Aucun résultat|j})} />)}
  </>;
};
