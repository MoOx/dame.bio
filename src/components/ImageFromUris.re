open Belt;
open ReactNative;

type uri = {
  .
  "name": option(string),
  "width": option(string),
  "sourceUrl": option(string),
};

[@react.component]
let make = (~uris: array(uri), ~resizeMode=?, ~style as s=?) => {
  let (loaded, setLoaded) = React.useState(() => false);
  let onLoadEnd =
    React.useCallback1(
      () => {
        setLoaded(_ => true);
        ();
      },
      [|setLoaded|],
    );
  let (layout, setLayout) = React.useState(() => None);
  let onLayout =
    React.useCallback1(
      (e: Event.layoutEvent) => {
        let layout = e.nativeEvent.layout;
        setLayout(_ => Some(layout));
      },
      [|setLayout|],
    );
  let sorted =
    uris->SortArray.stableSortBy((uri, uri2) =>
      uri##width->Option.map(int_of_string)->Option.getWithDefault(0)
      - uri2##width->Option.map(int_of_string)->Option.getWithDefault(0)
    );
  let firstItem = sorted[0];
  let smallerSourceUri = firstItem->Option.flatMap(uri => uri##sourceUrl);
  let adaptedSourceUri =
    layout
    ->Option.map(l =>
        sorted->Array.keep(uri =>
          uri##width->Option.map(float_of_string)->Option.getWithDefault(0.)
          > l.width
          *. PixelRatio.get()
        )
      )
    ->Option.flatMap(candidates => candidates[0])
    ->Option.flatMap(uri => uri##sourceUrl)
    ->Option.getWithDefault(smallerSourceUri->Option.getWithDefault(""));
  smallerSourceUri
  ->Option.map(smallerSourceUri =>
      <ViewportObserver
        style=Style.(arrayOption([|Some(StyleSheet.absoluteFill), s|]))>
        ...{state =>
          <Image
            ?resizeMode
            style=Style.(arrayOption([|Some(StyleSheet.absoluteFill), s|]))
            blurRadius=?{state##hasBeenVisible && loaded ? None : Some(4.)}
            onLoadEnd
            onLayout
            source=Image.(
              Source.fromUriSource(
                uriSource(
                  ~uri=
                    state##hasBeenVisible
                      ? adaptedSourceUri : smallerSourceUri,
                  (),
                ),
              )
            )
            // SSR workaround https://github.com/necolas/react-native-web/issues/543
            defaultSource=Image.(
              DefaultSource.fromUri(~uri=smallerSourceUri, ())
            )
          />
        }
      </ViewportObserver>
    )
  ->Option.getWithDefault(<View style=?s />);
};
