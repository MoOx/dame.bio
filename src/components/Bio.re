open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "bioText":
        style([
          fontWeight(`_300),
          color(String("#49443A")),
          maxWidth(Pt(500.)),
        ]),
    })
  );

[@react.component]
let make = () => {
  <Text style=styles##bioText>
    {j|Curieuse et gourmande, je vis dans la région toulousaine à la campagne. Passionnée de cuisine et de potager bio, je crée des recettes sans gluten, souvent sans lactose et parfois sans oeufs.|j}
    ->React.string
  </Text>;
};
