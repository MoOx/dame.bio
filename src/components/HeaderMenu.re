open Helpers;

open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderMenu");

let styles =
  StyleSheet.create(
    Style.{
      "menu":
        style([
          flexDirection(Row),
          maxWidth(Pt(1000.)),
          width(Pct(100.)),
          justifyContent(Center),
        ]),
      "menuLinks":
        style([
          zIndex(1),
          flex(1.),
          maxWidth(Pt(1000.)),
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(SpaceBetween),
        ]),
      "menuLink":
        style([
          flexGrow(1.),
          fontFamily("IndieFlower"),
          fontWeight(`Bold),
          fontSize(Float(24.)),
          paddingHorizontal(Pt(20.)),
          lineHeight(65.), /* 73 - transparent part */
          textAlign(Center),
          color(String("#4E7E3B")),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##menu>
      <div
        style={
          ReactDOMRe.Style.make(
            ~position="absolute",
            ~top="0",
            ~left="0",
            ~right="0",
            ~height="73px",
            ~background="url(/images/green/ribbon-tile.png) repeat-x",
            (),
          )
        }
      />
      <div
        style={
          ReactDOMRe.Style.make(
            ~position="absolute",
            ~top="0",
            ~left="-110px",
            ~width="806px",
            ~height="73px",
            ~background="url(/images/green/menu-ribbon-left.png) repeat-x",
            (),
          )
        }
      />
      <div
        style={
          ReactDOMRe.Style.make(
            ~position="absolute",
            ~top="0",
            ~right="-110px",
            ~width="806px",
            ~height="73px",
            ~background="url(/images/green/menu-ribbon-right.png) repeat-x",
            (),
          )
        }
      />
      <View style=styles##menuLinks>
        <Spacer size=L />
        <TextLink style=styles##menuLink href="/alimentation/">
          {{j|Alimentation|j} |> text}
        </TextLink>
        <TextLink style=styles##menuLink href="/permaculture/">
          {{j|Permaculture|j} |> text}
        </TextLink>
        <TextLink style=styles##menuLink href="/bien-etre/">
          {{j|Bien-être|j} |> text}
        </TextLink>
        <TextLink style=styles##menuLink href="/lifestyle/">
          {{j|Lifestyle|j} |> text}
        </TextLink>
        <Spacer size=L />
      </View>
    </View>,
};
