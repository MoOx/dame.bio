open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([
          justifyContent(Center),
          backgroundColor(String("#fefefe")),
        ]),
      "image": style([alignSelf(Center)]),
    },
  );

let component = ReasonReact.statelessComponent("Footer");

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##container>
      <Spacer size=XL />
      <InstagramFeed />
      <Container />
      <Spacer size=XL />
      <Image
        style=styles##image
        source={
                 `URI(
                   Image.(
                     imageURISource(
                       ~uri="/images/pink/footer-flowers.png",
                       ~width=Pt(1800. *. 0.75),
                       ~height=Pt(324. *. 0.75),
                       (),
                     )
                   ),
                 )
               }
      />
    </View>,
};
