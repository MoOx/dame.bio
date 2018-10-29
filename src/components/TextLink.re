open BsReactNative;

module type TextLinkComponent = {
  let make:
    (
      ~href: string=?,
      ~accessible: bool=?,
      ~allowFontScaling: bool=?,
      ~ellipsizeMode: [ | `clip | `head | `middle | `tail]=?,
      ~numberOfLines: int=?,
      ~onLayout: MyRNEvent.NativeLayoutEvent.t => unit=?,
      ~onLongPress: unit => unit=?,
      ~onPress: unit => unit=?,
      ~pressRetentionOffset: MyTypesRN.insets=?,
      ~selectable: bool=?,
      ~style: Style.t=?,
      ~testID: string=?,
      ~selectionColor: string=?,
      ~textBreakStrategy: [ | `simple | `highQuality | `balanced]=?,
      ~adjustsFontSizeToFit: bool=?,
      ~minimumFontScale: float=?,
      ~suppressHighlighting: bool=?,
      ~value: string=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.component(
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      unit
    );
};

module CreateComponent = (Impl: View.Impl) : TextLinkComponent => {
  let make =
      (
        ~href=?,
        ~accessible=?,
        ~allowFontScaling=?,
        ~ellipsizeMode=?,
        ~numberOfLines=?,
        ~onLayout=?,
        ~onLongPress=?,
        ~onPress=?,
        ~pressRetentionOffset=?,
        ~selectable=?,
        ~style=?,
        ~testID=?,
        ~selectionColor=?,
        ~textBreakStrategy=?,
        ~adjustsFontSizeToFit=?,
        ~minimumFontScale=?,
        ~suppressHighlighting=?,
        ~value=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=Impl.view,
      ~props=
        Js.Undefined.(
          {
            "href": fromOption(href),
            "accessibilityRole": "link",
            "accessible": fromOption(MyUtilsRN.optBoolToOptJsBoolean(accessible)),
            "allowFontScaling":
              fromOption(MyUtilsRN.optBoolToOptJsBoolean(allowFontScaling)),
            "ellipsizeMode":
              fromOption(
                MyUtilsRN.option_map(
                  fun
                  | `head => "head"
                  | `middle => "middle"
                  | `tail => "tail"
                  | `clip => "clip",
                  ellipsizeMode
                )
              ),
            "numberOfLines": fromOption(numberOfLines),
            "onLayout": fromOption(onLayout),
            "onLongPress": fromOption(onLongPress),
            "onPress": fromOption(onPress),
            "pressRetentionOffset": fromOption(pressRetentionOffset),
            "selectable": fromOption(MyUtilsRN.optBoolToOptJsBoolean(selectable)),
            "style": fromOption(style),
            "testID": fromOption(testID),
            "selectionColor": fromOption(selectionColor),
            "textBreakStrategy":
              fromOption(
                MyUtilsRN.option_map(
                  fun
                  | `simple => "simple"
                  | `highQuality => "highQuality"
                  | `balanced => "balanced",
                  textBreakStrategy
                )
              ),
            "adjustsFontSizeToFit":
              fromOption(MyUtilsRN.optBoolToOptJsBoolean(adjustsFontSizeToFit)),
            "minimumFontScale": fromOption(minimumFontScale),
            "suppressHighlighting":
              fromOption(MyUtilsRN.optBoolToOptJsBoolean(suppressHighlighting))
          }
        ),
      switch value {
      | Some(string) =>
        Array.append([|ReasonReact.stringToElement(string)|], children)
      | None => children
      }
    );
};

include
  CreateComponent(
    {
      [@bs.module "react-native"]
      external view : ReasonReact.reactClass = "Text";
    }
  );
