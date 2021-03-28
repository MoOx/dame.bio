open Belt;
open ReactNative;

open WPGraphQL.GetPagesAndPosts.GetPagesAndPosts_inner;

[@react.component]
let make = (~posts, ~categorySlug, ~tagSlug) => {
  let pageInfo = posts->Option.flatMap(p => p.pageInfo);
  <>
    {posts
     ->Option.flatMap(p => p.nodes)
     ->Option.map(nodes =>
         <>
           <PostList nodes />
           <View
             style=Style.(
               style(~flexDirection=`row, ~justifyContent=`spaceAround, ())
             )>
             {pageInfo
              ->Option.map(p => p.hasPreviousPage)
              ->Option.getWithDefault(false)
                ? pageInfo
                  ->Option.flatMap(p => p.startCursor)
                  ->Option.map(cursor =>
                      <BannerButton
                        href={
                          "/"
                          ++ categorySlug->Option.mapWithDefault("", c =>
                               c ++ "/"
                             )
                          ++ tagSlug->Option.mapWithDefault("", t =>
                               "tag/" ++ t ++ "/"
                             )
                          ++ "before/"
                          ++ cursor
                        }>
                        {j|Articles plus récents|j}->React.string
                      </BannerButton>
                    )
                  ->Option.getWithDefault(React.null)
                : React.null}
             {pageInfo
              ->Option.map(p => p.hasNextPage)
              ->Option.getWithDefault(false)
                ? pageInfo
                  ->Option.flatMap(p => p.endCursor)
                  ->Option.map(cursor =>
                      <BannerButton
                        href={
                          "/"
                          ++ categorySlug->Option.mapWithDefault("", c =>
                               c ++ "/"
                             )
                          ++ tagSlug->Option.mapWithDefault("", t =>
                               "tag/" ++ t ++ "/"
                             )
                          ++ "after/"
                          ++ cursor
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
