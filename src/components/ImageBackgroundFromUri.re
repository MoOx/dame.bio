open ReactNative;

[@react.component]
let make = (~uri, ~resizeMode=?, ~style=?, ~children, ()) => {
  <ImageBackground
    ?resizeMode
    ?style
    source=Image.(Source.fromUriSource(uriSource(~uri, ())))
    // SSR workaround https://github.com/necolas/react-native-web/issues/543
    defaultSource={Image.DefaultSource.fromUri(~uri, ())}>
    children
  </ImageBackground>;
};
