open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderLargeMenu");

let styles =
  StyleSheet.create(
    Style.{
      "wrapper":
        style([
          flexDirection(Row),
          maxWidth(Pt(1000.)),
          width(Pct(100.)),
          justifyContent(Center),
        ]),
      "container":
        style([
          zIndex(1),
          flex(1.),
          maxWidth(Pt(1000.)),
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(SpaceBetween),
        ]),
      "item": style([flexGrow(1.), paddingHorizontal(Pt(20.))]),
      "itemText":
        style([
          fontFamily("IndieFlower"),
          fontWeight(`Bold),
          fontSize(Float(24.)),
          lineHeight(65.), /* 73 - transparent part */
          textAlign(Center),
          color(String("#4E7E3B")),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##wrapper>
      <div
        style={ReactDOMRe.Style.make(
          ~position="absolute",
          ~top="0",
          ~left="0",
          ~right="0",
          ~height="73px",
          ~background="url(/images/green/ribbon-tile.png) repeat-x",
          (),
        )}
      />
      <div
        style={ReactDOMRe.Style.make(
          ~position="absolute",
          ~top="0",
          ~left="-110px",
          ~width="806px",
          ~height="73px",
          ~background="url(/images/green/menu-ribbon-left.png) repeat-x",
          (),
        )}
      />
      <div
        style={ReactDOMRe.Style.make(
          ~position="absolute",
          ~top="0",
          ~right="-110px",
          ~width="806px",
          ~height="73px",
          ~background="url(/images/green/menu-ribbon-right.png) repeat-x",
          (),
        )}
      />
      <View style=styles##container>
        <Spacer size=L />
        <TouchableOpacityLink style=styles##item href="/alimentation/">
          <Text style=styles##itemText>
            {j|Alimentation|j}->ReasonReact.string
          </Text>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##item href="/permaculture/">
          <Text style=styles##itemText>
            {j|Permaculture|j}->ReasonReact.string
          </Text>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##item href="/bien-etre/">
          <Text style=styles##itemText>
            {j|Bien-être|j}->ReasonReact.string
          </Text>
        </TouchableOpacityLink>
        <TouchableOpacityLink style=styles##item href="/lifestyle/">
          <Text style=styles##itemText>
            {j|Lifestyle|j}->ReasonReact.string
          </Text>
        </TouchableOpacityLink>
        <Spacer size=L />
      </View>
    </View>,
};
