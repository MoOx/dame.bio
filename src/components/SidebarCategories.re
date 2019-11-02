open Belt;
open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "categories":
        style(
          ~width=100.->pct,
          ~maxWidth=400.->dp,
          // ~alignItems=`center,
          ~borderRadius=6.,
          ~backgroundColor=Consts.Colors.lightest,
          ~shadowColor="#333333",
          ~shadowOffset=offset(~height=4., ~width=0.),
          ~shadowOpacity=0.05,
          ~shadowRadius=20.,
          (),
        ),
      "sep":
        style(
          ~backgroundColor=Consts.Colors.pink,
          ~height=2.->dp,
          ~width=100.->pct,
          ~opacity=0.4,
          (),
        ),
      "link": style(~color=Consts.Colors.dark, ()),
    })
  );

module GetCategories = [%graphql
  {|
  query getCategories {
    menu(id: "TWVudTo1ODM=") {
      menuItems {
        nodes {
          label
          url
        }
      }
    }
  }
|}
];

module GetCategoriesQuery = ReasonApollo.CreateQuery(GetCategories);

[@react.component]
let make = () => {
  let itemsQuery = GetCategories.make();
  <SpacedView style=styles##categories>
    <GetCategoriesQuery variables=itemsQuery##variables>
      ...{({result}) =>
        switch (result) {
        | Loading => <LoadingIndicator />
        | Error(error) => React.null
        | Data(response) =>
          response##menu
          ->Option.flatMap(cs =>
              cs##menuItems
              ->Option.flatMap(maybeItems =>
                  maybeItems##nodes
                  ->Option.map(items =>
                      items
                      ->Array.mapWithIndex((index, maybeItem) =>
                          maybeItem
                          ->Option.flatMap(item =>
                              item##label
                              ->Option.flatMap(c =>
                                  item##url
                                  ->Option.map(url =>
                                      <>
                                        {index == 0
                                           ? React.null
                                           : <View style=styles##sep />}
                                        <ViewLink
                                          key=url
                                          href={
                                            url->Js.String.replace(
                                                   Consts.backendUrl
                                                   ++ "category/",
                                                   "/",
                                                   _,
                                                 )
                                            ++ "/"
                                          }>
                                          <SpacedView
                                            vertical=S horizontal=XXS>
                                            <Text style=styles##link>
                                              c->React.string
                                            </Text>
                                          </SpacedView>
                                        </ViewLink>
                                      </>
                                    )
                                )
                            )
                          ->Option.getWithDefault(React.null)
                        )
                      ->React.array
                    )
                )
            )
          ->Option.getWithDefault(React.null)
        }
      }
    </GetCategoriesQuery>
  </SpacedView>;
};
