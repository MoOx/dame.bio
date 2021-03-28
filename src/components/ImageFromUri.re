open ReactNative;

[@react.component]
let make = (~uri, ~resizeMode=?, ~style=?, ~ssr=true, ()) => {
  <Image
    ?resizeMode
    ?style
    source=Image.(Source.fromUriSource(uriSource(~uri, ())))
    // SSR workaround https://github.com/necolas/react-native-web/issues/543
    defaultSource=?{ssr ? Some(Image.DefaultSource.fromUri(~uri, ())) : None}
  />;
};
