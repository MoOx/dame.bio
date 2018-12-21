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
          borderColor(String("#E3E4E5")),
        ]),
      "container":
        style([
          flexDirection(Row),
          minHeight(Pt(50.)),
          alignItems(Center),
        ]),
      "itemWrapper": style([flex(1.)]),
      "item": style([justifyContent(Center), alignItems(Center)]),
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
        <TouchableOpacityLink style=styles##itemWrapper href="/">
          <View style=styles##item>
            <SVGMenuHome
              width=24.
              height=24.
              fill={false ? colorInActive : colorActive}
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  false ? style([]) : styles##itemTextActive,
                ])
              )>
              {j|Accueil|j}->ReasonReact.string
            </Text>
          </View>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##itemWrapper href="/alimentation/">
          <View style=styles##item>
            <SVGMenuAlimentation width=24. height=24. fill=colorInActive />
            <Text style=styles##itemText>
              {j|Alimentation|j}->ReasonReact.string
            </Text>
          </View>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##itemWrapper href="/permaculture/">
          <View style=styles##item>
            <SVGMenuPermaculture width=24. height=24. fill=colorInActive />
            <Text style=styles##itemText>
              {j|Permaculture|j}->ReasonReact.string
            </Text>
          </View>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##itemWrapper href="/bien-etre/">
          <View style=styles##item>
            <SVGMenuBienEtre width=24. height=24. fill=colorInActive />
            <Text style=styles##itemText>
              {j|Bien-être|j}->ReasonReact.string
            </Text>
          </View>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##itemWrapper href="/lifestyle/">
          <View style=styles##item>
            <SVGMenuLifestyle width=24. height=24. fill=colorInActive />
            <Text style=styles##itemText>
              {j|Lifestyle|j}->ReasonReact.string
            </Text>
          </View>
        </TouchableOpacityLink>
      </View>
    </SafeAreaView>,
};
