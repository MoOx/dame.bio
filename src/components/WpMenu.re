open Belt;
open ReactNative;

module GetWpMenu = [%graphql
  {|
  query getWpMenu($id: ID!) {
    menu(id: $id) {
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

module GetWpMenuQuery = ReasonApollo.CreateQuery(GetWpMenu);

type renderItem =
  (~url: string, ~label: string, ~isActive: bool) => React.element;

[@react.component]
let make = (~id, ~currentLocation, ~renderItem) => {
  let itemsQuery = GetWpMenu.make(~id, ());
  <GetWpMenuQuery variables=itemsQuery##variables>
    ...{({result}) =>
      switch (result) {
      | Loading => <ActivityIndicator size=ActivityIndicator.Size.small />
      | Error(error) =>
        Js.Console.error(error);
        React.null;
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
                            ->Option.flatMap(label =>
                                item##url
                                ->Option.map(url => {
                                    let cleanUrl =
                                      url
                                      ->Js.String.replace(
                                          Consts.backendUrl,
                                          "",
                                          _,
                                        )
                                      ->Js.String.replace(
                                          "/category/",
                                          "/",
                                          _,
                                        );

                                    let isActive =
                                      currentLocation##pathname
                                      ->Js.String.startsWith(cleanUrl, _);
                                    renderItem(
                                      ~index,
                                      ~url=cleanUrl,
                                      ~label,
                                      ~isActive,
                                    );
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
  </GetWpMenuQuery>;
};
