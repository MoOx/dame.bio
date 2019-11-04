open Belt;
open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "categories":
        style(
          ~width=100.->pct,
          ~maxWidth=400.->dp,
          // ~alignItems=`center,
          ~borderRadius=6.,
          ~backgroundColor=Consts.Colors.lightest,
          ~shadowColor="#333333",
          ~shadowOffset=offset(~height=4., ~width=0.),
          ~shadowOpacity=0.05,
          ~shadowRadius=20.,
          (),
        ),
      "sep":
        style(
          ~backgroundColor=Consts.Colors.pink,
          ~height=2.->dp,
          ~width=100.->pct,
          ~opacity=0.4,
          (),
        ),
      "link": style(~color=Consts.Colors.dark, ()),
    })
  );

let renderItem = (~index, ~url, ~label, ~isActive as _) => {
  <View key=url>
    {index == 0 ? React.null : <View style=styles##sep />}
    <ViewLink href=url>
      <SpacedView vertical=S horizontal=XXS>
        <Text style=styles##link> label->React.string </Text>
      </SpacedView>
    </ViewLink>
  </View>;
};

[@react.component]
let make = () => {
  <SpacedView style=styles##categories>
    <WpMenu id="TWVudTo1ODM=" currentLocation={"pathname": ""} renderItem />
  </SpacedView>;
};
