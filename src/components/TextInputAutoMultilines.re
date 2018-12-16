open BsReactNative;

type action =
  | UpdateHeight(float);

type state = {height: float};

let component = ReasonReact.reducerComponent("TextInputAutoMultilines");

let make =
    (~value, ~style, ~placeholder, ~onFocus, ~onChangeText, ~minHeight=40., _) => {
  ...component,
  initialState: () => {height: 0.},
  reducer: (action, _) =>
    switch (action) {
    | UpdateHeight(height) => ReasonReact.Update({height: height})
    },
  render: ({state, send}) =>
    <TextInput
      multiline=true
      onContentSizeChange={event =>
        /* native only https://github.com/necolas/react-native-web/issues/793 */
        send(UpdateHeight(event##nativeEvent##contentSize##height))}
      onChange={() =>
        switch (Platform.os()) {
        | exception (Platform.UnknownPlatform(os)) when os == "web" =>
          /* https://github.com/necolas/react-native-web/issues/793#issuecomment-437549351 */
          let event = [%raw "arguments[0]"];
          send(UpdateHeight(event##nativeEvent##srcElement##scrollHeight));
        | _ => ()
        }
      }
      style={Style.concat([
        style,
        Style.style([Style.height(Pt(max(minHeight, state.height)))]),
      ])}
      value
      placeholder
      onFocus
      onChangeText
    />,
};
