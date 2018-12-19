open BsReactNative;

let colorInActive = "#909192";
let colorActive = "#FD2E55";

let component = ReasonReact.statelessComponent("HeaderMenu");

let styles =
  StyleSheet.create(
    Style.{
      "wrapper":
        style([
          borderTopWidth(StyleSheet.hairlineWidth),
          borderColor(String("#C4C7CD")),
          /* backgroundColor(String("#FDFFFF")), */
        ]),
      "container":
        style([flexDirection(Row), height(Pt(50.)), alignItems(Center)]),
      "item":
        style([
          display(Flex),
          flex(1.),
          flexDirection(Column),
          justifyContent(Center),
          alignItems(Center),
        ]),
      "itemText":
        style([
          flex(1.),
          color(String(colorInActive)),
          fontSize(Float(10.)),
          marginTop(Pt(1.5)),
        ]),
      "itemTextActive": style([color(String(colorActive))]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <SafeAreaView style=styles##wrapper>
      <View style=styles##container>
        <TextLink style=styles##item href="/">
          <SVGMenuHome width=24. height=24. fill=colorActive />
          <Text
            style=Style.(
              concat([
                styles##itemText,
                false ? style([]) : styles##itemTextActive,
              ])
            )>
            {j|Accueil|j}->ReasonReact.string
          </Text>
        </TextLink>
        <TextLink style=styles##item href="/alimentation/">
          <SVGMenuAlimentation width=24. height=24. fill=colorInActive />
          <Text style=styles##itemText>
            {j|Alimentation|j}->ReasonReact.string
          </Text>
        </TextLink>
        <TextLink style=styles##item href="/permaculture/">
          <SVGMenuPermaculture width=24. height=24. fill=colorInActive />
          <Text style=styles##itemText>
            {j|Permaculture|j}->ReasonReact.string
          </Text>
        </TextLink>
        <TextLink style=styles##item href="/bien-etre/">
          <SVGMenuBienEtre width=24. height=24. fill=colorInActive />
          <Text style=styles##itemText>
            {j|Bien-être|j}->ReasonReact.string
          </Text>
        </TextLink>
        <TextLink style=styles##item href="/lifestyle/">
          <SVGMenuLifestyle width=24. height=24. fill=colorInActive />
          <Text style=styles##itemText>
            {j|Lifestyle|j}->ReasonReact.string
          </Text>
        </TextLink>
      </View>
    </SafeAreaView>,
};
