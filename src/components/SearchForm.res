open ReactNative

@react.component
let make = () => {
  let (value, value_set) = React.useState(() => "")

  let router = Next.useRouter()
  let submit = React.useCallback2(() => {
    router->Next.Router.push("/recherche#" ++ Utils.encodeURIComponent(value))
  }, (router, value))

  <View
    style={
      open Style
      style(~flexDirection=#row, ~flexShrink=1., ~alignItems=#center, ())
    }>
    <TextInput
      style={
        open Style
        style(
          ~display=#flex,
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
      }
      placeholder="Rechercher"
      placeholderTextColor=Consts.Colors.main
      value
      onChangeText={value => value_set(_ => value)}
      onSubmitEditing={_ => submit()}
      clearButtonMode=#always
    />
    <Text
      style={
        open Style
        style(
          ~display=#flex,
          ~paddingVertical=4.->dp,
          ~paddingHorizontal=8.->dp,
          ~borderTopRightRadius=5.,
          ~borderBottomRightRadius=5.,
          ~backgroundColor="rgba(255,255,255,0.4)",
          (),
        )
      }
      onPress={_ => submit()}>
      <SVGSearch fill=Consts.Colors.main width="16" height="16" />
    </Text>
  </View>
}
