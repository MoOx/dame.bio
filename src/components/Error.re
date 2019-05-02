open BsReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container": style([justifyContent(Center), alignItems(Center)]),
      "oops":
        style([
          fontSize(Float(64.)),
          lineHeight(64.),
          color(String("#ddd")),
        ]),
      "title":
        style([
          margin(Pt(60.)),
          fontSize(Float(24.)),
          lineHeight(48.),
          textAlign(Center),
        ]),
    })
  );

[@react.component]
let make = (~label, ()) => {
  let errorText =
    switch (label) {
    | None => "Une erreur est survenue"
    | Some(label) => label
    };
  <SpacedView vertical=XXL horizontal=None>
    <Text style=styles##oops> "Ouuuups!"->React.string </Text>
    <View>
      <Text style=styles##title>
        /* <strong>{status |>text}</strong> */
         errorText->React.string </Text>
    </View>
  </SpacedView>;
  /*
   {status === 404 && (
     <View>
       <Text>
         {"It seems you found a broken link. "}
         {"Sorry about that. "}
         <br />
         {"Do not hesitate to report this page."}
       </Text>
     </View>
   )}
   */
};
