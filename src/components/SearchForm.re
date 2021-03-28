open ReactNative;

type state = {
  value: string,
  focus: bool,
};

type action =
  | Focus
  | Blur
  | Edit(string)
  | Submit;

[@react.component]
let make = () =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,
    initialState: () => {value: "", focus: false},
    reducer: (action, state) =>
      switch (action) {
      | Focus => ReactCompat.Update({...state, focus: true})
      | Blur => ReactCompat.Update({...state, focus: false})
      | Edit(value) => ReactCompat.Update({...state, value})
      | Submit =>
        ReactCompat.SideEffects(
          _ =>
            Linking.openURL(
              "https://www.ecosia.org/search?q=site%3Adame.bio+"
              ++ Utils.encodeURIComponent(state.value),
            )
            ->ignore,
        )
      },
    render: ({state, send}) =>
      <View
        style=Style.(
          style(~flexDirection=`row, ~flexShrink=1., ~alignItems=`center, ())
        )>
        <TextInput
          style=Style.(
            style(
              ~display=`flex,
              ~flexGrow=1.,
              ~flexShrink=1.,
              ~minWidth=0.->dp,
              ~maxWidth=120.->dp,
              ~margin=0.->dp,
              ~paddingVertical=4.->dp,
              ~paddingHorizontal=8.->dp,
              ~borderTopLeftRadius=5.,
              ~borderBottomLeftRadius=5.,
              ~fontSize=13.,
              ~color=Consts.Colors.lightest,
              ~backgroundColor="rgba(255,255,255,0.4)",
              (),
            )
          )
          placeholder="Rechercher"
          placeholderTextColor=Consts.Colors.main
          value={state.value}
          onFocus={_ => send(Focus)}
          onBlur={_ => send(Blur)}
          onChangeText={value => send(Edit(value))}
          onSubmitEditing={_ => send(Submit)}
          clearButtonMode=`always
        />
        <Text
          style=Style.(
            style(
              ~display=`flex,
              ~paddingVertical=4.->dp,
              ~paddingHorizontal=8.->dp,
              ~borderTopRightRadius=5.,
              ~borderBottomRightRadius=5.,
              ~backgroundColor="rgba(255,255,255,0.4)",
              (),
            )
          )
          onPress={_ => send(Submit)}>
          <SVGSearch fill=Consts.Colors.main width="16" height="16" />
        </Text>
      </View>,
  });
