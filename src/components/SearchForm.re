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

let make = _ => {
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
    <View style=Style.(style([flexDirection(Row), alignItems(Center)]))>
      <TextInput
        style=Style.(
          style([
            margin(Pt(0.)),
            paddingVertical(Pt(4.)),
            paddingHorizontal(Pt(8.)),
            borderTopLeftRadius(5.),
            borderBottomLeftRadius(5.),
            borderWidth(1.),
            fontSize(Float(13.)),
            color(String(Consts.Colors.dark)),
            borderColor(String(Consts.Colors.light)),
            backgroundColor(String(Consts.Colors.lightest)),
            width(Pt(140.)),
          ])
        )
        placeholder="Rechercher..."
        placeholderTextColor=Consts.Colors.main
        value={state.value}
        onFocus={() => send(Focus)}
        onBlur={() => send(Blur)}
        onChangeText={value => send(Edit(value))}
        onSubmitEditing={() => send(Submit)}
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
            backgroundColor(String(Consts.Colors.main)),
            borderStyle(Solid),
            borderColor(String(Consts.Colors.light)),
            borderTopWidth(1.),
            borderRightWidth(1.),
            borderBottomWidth(1.),
          ])
        )
        onPress={() => send(Submit)}>
        <SVGSearch fill=Consts.Colors.light />
      </Text>
    </View>,
};
