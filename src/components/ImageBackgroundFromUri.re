open BsReactNative;

let component = ReasonReact.statelessComponent("ImageBackgroundFromUri");

let make = (~uri, ~resizeMode=?, ~style=?, _children) => {
  ...component,
  render: _self =>
    ReasonReact.element(
      ImageBackground.make(
        ~resizeMode?,
        ~style?,
        ~source={
          `URI(Image.(imageURISource(~uri, ())));
        },
        /* SSR workaround https://github.com/necolas/react-native-web/issues/543 */
        ~defaultSource={
          `URI(Image.(defaultURISource(~uri, ())));
        },
        _children,
      ),
    ),
};
