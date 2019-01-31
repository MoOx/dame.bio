open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "container":
        style([
          justifyContent(Center),
          backgroundColor(String("#fefefe")),
          /* For the image on small screen */
          overflow(Hidden),
        ]),
      "image": style([alignSelf(Center)]),
    },
  );

let component = ReasonReact.statelessComponent("Footer");

let uri = "/images/footer-flowers.png";
let width: Style.pt_only = Style.Pt(1800. *. 0.75);
let height: Style.pt_only = Style.Pt(324. *. 0.75);

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
        source={`URI(Image.(imageURISource(~uri, ~width, ~height, ())))}
        defaultSource={
                        `URI(
                          Image.(defaultURISource(~uri, ~width, ~height, ())),
                        )
                      }
      />
    </View>,
};
