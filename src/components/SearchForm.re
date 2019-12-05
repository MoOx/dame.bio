open BsReactNative;

type state = {
  value: string,
  focus: bool,
};

type action =
  | Focus
  | Blur
  | Edit(string)
  | Submit;

let component = ReasonReact.reducerComponent("SearchForm");

[@react.component]
let make = () =>
  ReactCompat.useRecordApi({
    ...component,
    initialState: () => {value: "", focus: false},
    reducer: (action, state) =>
      switch (action) {
      | Focus => ReasonReact.Update({...state, focus: true})
      | Blur => ReasonReact.Update({...state, focus: false})
      | Edit(value) => ReasonReact.Update({...state, value})
      | Submit =>
        ReasonReact.SideEffects(
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
          style([flexDirection(Row), flexShrink(1.), alignItems(Center)])
        )>
        <TextInput
          style=Style.(
            style([
              display(Flex),
              flexGrow(1.),
              flexShrink(1.),
              minWidth(Pt(0.)),
              maxWidth(Pt(120.)),
              margin(Pt(0.)),
              paddingVertical(Pt(4.)),
              paddingHorizontal(Pt(8.)),
              borderTopLeftRadius(5.),
              borderBottomLeftRadius(5.),
              fontSize(Float(13.)),
              color(String(Consts.Colors.lightest)),
              backgroundColor(String("rgba(255,255,255,0.4)")),
            ])
          )
          placeholder="Rechercher"
          placeholderTextColor=Consts.Colors.main
          value={state.value}
          onFocus={() => send(Focus)}
          onBlur={() => send(Blur)}
          onChangeText={value => send(Edit(value))}
          onSubmitEditing={_ => send(Submit)}
          clearButtonMode=`always
        />
        <Text
          style=Style.(
            style([
              display(Flex),
              paddingVertical(Pt(4.)),
              paddingHorizontal(Pt(8.)),
              borderTopRightRadius(5.),
              borderBottomRightRadius(5.),
              backgroundColor(String("rgba(255,255,255,0.4)")),
            ])
          )
          onPress={_ => send(Submit)}>
          <SVGSearch fill=Consts.Colors.main />
        </Text>
      </View>,
  });
