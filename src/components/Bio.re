open BsReactNative;
open Helpers;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.{
      "bioText": style([fontWeight(`_300), color(String("#49443A"))]),
    },
  );

let make = _ => {
  ...component,
  render: _self =>
    <Text style=styles##bioText>
      {
        {j|Curieuse et gourmande, je vis dans la région toulousaine à la campagne. Passionnée de cuisine et de potager bio, je crée des recettes sans gluten, souvent sans lactose et parfois sans oeufs.|j}
        |> text
      }
    </Text>,
};
