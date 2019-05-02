open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "title":
        style([
          fontSize(Float(28.)),
          lineHeight(28. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
    })
  );

[@react.component]
let make = (~items: list(Structures.post), ()) => {
  switch (items) {
  | [] => React.null
  | _ =>
    <>
      <SpacedView>
        <Text style=styles##title>
          {j|Dans le même style|j}->React.string
        </Text>
      </SpacedView>
      <PostList posts=items />
    </>
  };
};
