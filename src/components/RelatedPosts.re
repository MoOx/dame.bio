open Helpers;

open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "container": style([]),
      "title":
        style([
          fontSize(Float(28.)),
          lineHeight(28. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("RelatedPosts");

let make = (~items: list(Structures.post), _) => {
  ...component,
  render: _self =>
    switch (items) {
    | [] => nothing
    | _ =>
      <View style=styles##container>
        <View>
          <Text style=styles##title>
            {{j|Dans le même style|j} |> text}
          </Text>
        </View>
        <Spacer size=S />
        <PostList posts=items />
      </View>
    },
};
