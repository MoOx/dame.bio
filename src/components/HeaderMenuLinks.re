open Belt;
open ReactNative;

let textColor = Consts.Colors.light;

let styles =
  Style.(
    StyleSheet.create({
      "container": viewStyle(~flexDirection=`row, ()),
      "link":
        textStyle(
          ~padding=10.->dp,
          ~fontSize=14.,
          ~fontWeight=`_500,
          ~lineHeight=14. *. 2.,
          ~color=textColor,
          (),
        ),
      "linkActive":
        textStyle(
          ~textDecorationLine=`underline,
          ~textDecorationStyle=`solid,
          (),
        ),
    })
  );

module GetCategories = [%graphql
  {|
  query getCategories {
    menu(id: "TWVudTo5NTk=") {
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
let make = (~currentLocation, ()) => {
  let itemsQuery = GetCategories.make();
  <View style=styles##container>
    <GetCategoriesQuery variables=itemsQuery##variables>
      ...{({result}) =>
        switch (result) {
        | Loading => <ActivityIndicator size=ActivityIndicator.Size.small />
        | Error(error) => React.null
        | Data(response) =>
          response##menu
          ->Option.flatMap(cs =>
              cs##menuItems
              ->Option.flatMap(maybeItems =>
                  maybeItems##nodes
                  ->Option.map(items =>
                      items
                      ->Array.map(maybeItem =>
                          maybeItem
                          ->Option.flatMap(item =>
                              item##label
                              ->Option.flatMap(c =>
                                  item##url
                                  ->Option.map(url => {
                                      let slugWithSlashes =
                                        url->Js.String.replace(
                                               Consts.backendUrl ++ "category/",
                                               "/",
                                               _,
                                             )
                                        ++ "/";
                                      let isActive =
                                        currentLocation##pathname
                                        ->Js.String.startsWith(
                                            slugWithSlashes,
                                            _,
                                          );
                                      <TextLink
                                        key=slugWithSlashes
                                        href=slugWithSlashes
                                        style=Style.(
                                          arrayOption([|
                                            Some(styles##link),
                                            isActive
                                              ? Some(styles##linkActive)
                                              : None,
                                          |])
                                        )>
                                        c->React.string
                                      </TextLink>;
                                    })
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
  </View>;
};
