open ReactNative;

[@react.component]
let make = () => {
  let currentMoonPhase = Moon.currentPhase();
  <SpacedView
    style=Style.(
      style(
        ~width=100.->pct,
        ~maxWidth=400.->dp,
        ~alignItems=`center,
        ~borderRadius=Consts.Radius.box,
        ~backgroundColor=Consts.Colors.lightest,
        ~shadowColor="#333333",
        ~shadowOffset=offset(~height=4., ~width=0.),
        ~shadowOpacity=0.05,
        ~shadowRadius=20.,
        (),
      )
    )>
    <View>
      <Text
        style=Style.(
          style(
            ~fontSize=12.,
            ~fontWeight=`_600,
            ~color=Consts.Colors.grey,
            (),
          )
        )>
        {{j|Phase de la Lune|j}->String.uppercase->React.string}
      </Text>
      <Text style=Style.(style(~fontSize=36., ~fontWeight=`_100, ()))>
        (
          switch (currentMoonPhase.phase) {
          | New => {j|Nouvelle Lune|j}
          | WaxingCrescent => {j|Premier croissant|j}
          | Quarter => {j|Premier quartier|j}
          | WaxingGibbous => {j|Lune gibbeuse croissante|j}
          | Full => {j|Pleine Lune|j}
          | WaningGibbous => {j|Lune gibbeuse décroissante|j}
          | LastQuarter => {j|Dernier Quartier|j}
          | WaningCrescent => {j|Dernier croissant|j}
          }
        )
        ->React.string
      </Text>
    </View>
    <Spacer />
    <Text style=Style.(style(~fontSize=72., ~lineHeight=64., ()))>
      currentMoonPhase.unicode->React.string
    </Text>
  </SpacedView>;
};
