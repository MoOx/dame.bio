open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
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
    | [] => ReasonReact.null
    | _ =>
      <>
        <SpacedView>
          <Text style=styles##title>
            {j|Dans le même style|j}->ReasonReact.string
          </Text>
        </SpacedView>
        <PostList posts=items />
      </>
    },
};
