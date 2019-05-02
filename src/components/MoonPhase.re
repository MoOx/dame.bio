open BsReactNative;

[@react.component]
let make = () => {
  let currentMoonPhase = Moon.currentPhase();
  <SpacedView
    style=Style.(
      style([
        width(Pct(100.)),
        maxWidth(Pt(400.)),
        alignItems(Center),
        borderRadius(6.),
        backgroundColor(String(Consts.Colors.lightest)),
        shadowColor(String("#333333")),
        shadowOffset(~height=4., ~width=0.),
        shadowOpacity(0.05),
        shadowRadius(20.),
      ])
    )>
    <View>
      <Text
        style=Style.(
          style([
            fontSize(Float(12.)),
            fontWeight(`_600),
            color(String(Consts.Colors.grey)),
          ])
        )>
        {{j|Phase de la Lune|j}->String.uppercase->React.string}
      </Text>
      <Text style=Style.(style([fontSize(Float(36.)), fontWeight(`_100)]))>
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
    <Text style=Style.(style([fontSize(Float(72.)), lineHeight(64.)]))>
      currentMoonPhase.unicode->React.string
    </Text>
  </SpacedView>;
};
