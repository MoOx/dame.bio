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
          flex(1.),
          flexDirection(Row),
          minHeight(Pt(50.)),
          alignItems(Center),
        ]),
      "itemWrapper":
        style([display(Flex), flex(1.), justifyContent(Center)]),
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

let make = (~currentLocation, _children) => {
  ...component,
  render: _self => {
    <SafeAreaView style=styles##wrapper>
      <View style=styles##container>
        <ViewLink style=styles##itemWrapper href="/">
          <View style=styles##item>
            <SVGMenuHome
              width=24.
              height=24.
              fill={
                currentLocation##pathname == "/" ? colorActive : colorInActive
              }
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  currentLocation##pathname == "/" ?
                    styles##itemTextActive : style([]),
                ])
              )>
              {j|Accueil|j}->ReasonReact.string
            </Text>
          </View>
        </ViewLink>
        <ViewLink style=styles##itemWrapper href="/alimentation/">
          <View style=styles##item>
            <SVGMenuAlimentation
              width=24.
              height=24.
              fill={
                currentLocation##pathname
                |> Js.String.startsWith("/alimentation/") ?
                  colorActive : colorInActive
              }
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  currentLocation##pathname
                  |> Js.String.startsWith("/alimentation/") ?
                    styles##itemTextActive : style([]),
                ])
              )>
              {j|Alimentation|j}->ReasonReact.string
            </Text>
          </View>
        </ViewLink>
        <ViewLink style=styles##itemWrapper href="/permaculture/">
          <View style=styles##item>
            <SVGMenuPermaculture
              width=24.
              height=24.
              fill={
                currentLocation##pathname
                |> Js.String.startsWith("/permaculture/") ?
                  colorActive : colorInActive
              }
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  currentLocation##pathname
                  |> Js.String.startsWith("/permaculture/") ?
                    styles##itemTextActive : style([]),
                ])
              )>
              {j|Permaculture|j}->ReasonReact.string
            </Text>
          </View>
        </ViewLink>
        <ViewLink style=styles##itemWrapper href="/bien-etre/">
          <View style=styles##item>
            <SVGMenuBienEtre
              width=24.
              height=24.
              fill={
                currentLocation##pathname
                |> Js.String.startsWith("/bien-etre/") ?
                  colorActive : colorInActive
              }
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  currentLocation##pathname
                  |> Js.String.startsWith("/bien-etre/") ?
                    styles##itemTextActive : style([]),
                ])
              )>
              {j|Bien-être|j}->ReasonReact.string
            </Text>
          </View>
        </ViewLink>
        <ViewLink style=styles##itemWrapper href="/lifestyle/">
          <View style=styles##item>
            <SVGMenuLifestyle
              width=24.
              height=24.
              fill={
                currentLocation##pathname
                |> Js.String.startsWith("/lifestyle/") ?
                  colorActive : colorInActive
              }
            />
            <Text
              style=Style.(
                concat([
                  styles##itemText,
                  currentLocation##pathname
                  |> Js.String.startsWith("/lifestyle/") ?
                    styles##itemTextActive : style([]),
                ])
              )>
              {j|Lifestyle|j}->ReasonReact.string
            </Text>
          </View>
        </ViewLink>
      </View>
    </SafeAreaView>;
  },
};

[@bs.deriving abstract]
type jsProps = {currentLocation: {. "pathname": string}};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~currentLocation=jsProps->currentLocationGet, [||])
  );
