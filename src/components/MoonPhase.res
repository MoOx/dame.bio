open ReactNative

@react.component
let make = () => {
  let currentMoonPhase = Moon.currentPhase()
  <SpacedView
    style={
      open Style
      style(
        ~width=100.->pct,
        ~maxWidth=400.->dp,
        ~alignItems=#center,
        ~borderRadius=Consts.Radius.box,
        ~backgroundColor=Consts.Colors.lightest,
        ~shadowColor="#333333",
        ~shadowOffset=offset(~height=4., ~width=0.),
        ~shadowOpacity=0.05,
        ~shadowRadius=20.,
        (),
      )
    }>
    <View>
      <Text
        style={
          open Style
          style(~fontSize=12., ~fontWeight=#_600, ~color=Consts.Colors.grey, ())
        }>
        {j`Phase de la Lune`->Js.String.toUpperCase->React.string}
      </Text>
      <Text
        style={
          open Style
          style(~fontSize=36., ~fontWeight=#_100, ())
        }>
        {switch currentMoonPhase.phase {
        | New => j`Nouvelle Lune`
        | WaxingCrescent => j`Premier croissant`
        | Quarter => j`Premier quartier`
        | WaxingGibbous => j`Lune gibbeuse croissante`
        | Full => j`Pleine Lune`
        | WaningGibbous => j`Lune gibbeuse décroissante`
        | LastQuarter => j`Dernier Quartier`
        | WaningCrescent => j`Dernier croissant`
        }->React.string}
      </Text>
    </View>
    <Spacer />
    <Text
      style={
        open Style
        style(~fontSize=72., ~lineHeight=64., ())
      }>
      {currentMoonPhase.unicode->React.string}
    </Text>
  </SpacedView>
}
