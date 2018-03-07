open BsReactNative;

let component = ReasonReact.statelessComponent("Sidebar");

let styles =
  StyleSheet.create(
    Style.(
      {
        "sidebar": style([flex(1.), flexDirection(Row), flexBasis(Pt(350.))]),
        "bar": style([backgroundColor("#F2DBDD"), width(Pt(4.))]),
        "blocks": style([flex(1.)]),
        "block": style([]),
        "blockTitle":
          style([
            fontSize(Float(24.)),
            marginBottom(Pt(12.)),
            fontFamily("IndieFlower"),
            /* fontWeight(`Bold), */
            color("#DE6D88")
          ]),
        "blockText":
          style([fontWeight(`_300), marginBottom(Pt(12.)), color("#49443A")]),
        "icons": style([flexDirection(Row)]),
        "icon": style([padding(Pt(10.))]),
        "iconWrapper":
          style([
            backgroundColor("#DE6D88"),
            lineHeight(24.),
            padding(Pt(10.))
          ])
      }
    )
  );

let make = children => {
  ...component,
  render: _self =>
    <View style=styles##sidebar>
      <View style=styles##bar />
      <Spacer large=true />
      <View style=styles##blocks>
        <View style=styles##block>
          <Text style=styles##blockTitle>
            (ReasonReact.stringToElement({j|Bienvenue|j}))
          </Text>
          <Text style=styles##blockText>
            (
              ReasonReact.stringToElement(
                {j|Nulla minus aut mollitia rem voluptatem voluptas facere. Beatae aperiam qui et quia non dolorum esse. Illum quae totam cumque sint dolor nobis. Cum aut et qui aut adipisci debitis tempora. Tempore sit at sint et maxime rerum dolorem.|j}
              )
            )
          </Text>
        </View>
        <Spacer />
        <SocialIcons
          wrapperStyle=styles##icons
          iconStyle=styles##icon
          iconSize=24.
          iconWrapperFunc=(
            (~children) => <Text style=styles##iconWrapper> ...children </Text>
          )
        />
        <View> ...children </View>
      </View>
    </View>
};
