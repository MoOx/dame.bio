[@bs.module "../../../../src/components/TouchableScale.js"]
external reactClass: ReasonReact.reactClass = "default";

open BsReactNative;

[@bs.deriving abstract]
type jsProps = {
  [@bs.optional]
  defaultScale: float,
  [@bs.optional]
  activeScale: float,
  [@bs.optional]
  hoverScale: float,
  [@bs.optional]
  focusScale: float,
  [@bs.optional]
  tension: float,
  [@bs.optional]
  friction: float,
  [@bs.optional]
  pressInTension: float,
  [@bs.optional]
  pressInFriction: float,
  [@bs.optional]
  pressOutTension: float,
  [@bs.optional]
  pressOutFriction: float,
  [@bs.optional]
  mouseEnterTension: float,
  [@bs.optional]
  mouseEnterFriction: float,
  [@bs.optional]
  mouseLeaveTension: float,
  [@bs.optional]
  mouseLeaveFriction: float,
  [@bs.optional]
  hoverTension: float,
  [@bs.optional]
  hoverFriction: float,
  [@bs.optional]
  focusTension: float,
  [@bs.optional]
  focusFriction: float,
  [@bs.optional]
  useNativeDriver: bool,
  /* TouchableWithoutFeedback props */
  [@bs.optional]
  accessible: bool,
  [@bs.optional]
  accessibilityLabel: string,
  [@bs.optional]
  accessibilityComponentType: [
    | `none
    | `button
    | `radiobutton_checked
    | `radiobutton_unchecked
  ],
  [@bs.optional]
  accessibilityTraits:
    list(
      [
        | `none
        | `button
        | `link
        | `header
        | `search
        | `image
        | `selected
        | `plays
        | `key
        | `text
        | `summary
        | `disabled
        | `frequentUpdates
        | `startsMedia
        | `adjustable
        | `allowsDirectInteraction
        | `pageTurn
      ],
    ),
  [@bs.optional]
  delayLongPress: int,
  [@bs.optional]
  delayPressIn: int,
  [@bs.optional]
  delayPressOut: int,
  [@bs.optional]
  disabled: bool,
  [@bs.optional]
  hitSlop: Types.insets,
  [@bs.optional]
  onLayout: RNEvent.NativeLayoutEvent.t => unit,
  [@bs.optional]
  onLongPress: unit => unit,
  [@bs.optional]
  onPress: unit => unit,
  [@bs.optional]
  onPressIn: unit => unit,
  [@bs.optional]
  onPressOut: unit => unit,
  [@bs.optional]
  pressRetentionOffset: Types.insets,
  [@bs.optional]
  style: Style.t,
  [@bs.optional]
  testID: string,
};

let make =
    (
      ~defaultScale=?,
      ~activeScale=?,
      ~hoverScale=?,
      ~focusScale=?,
      ~tension=?,
      ~friction=?,
      ~pressInTension=?,
      ~pressInFriction=?,
      ~pressOutTension=?,
      ~pressOutFriction=?,
      ~mouseEnterTension=?,
      ~mouseEnterFriction=?,
      ~mouseLeaveTension=?,
      ~mouseLeaveFriction=?,
      ~hoverTension=?,
      ~hoverFriction=?,
      ~focusTension=?,
      ~focusFriction=?,
      ~useNativeDriver=?,
      /* TouchableWithoutFeedback props */
      ~accessible=?,
      ~accessibilityLabel=?,
      ~accessibilityComponentType=?,
      ~accessibilityTraits=?,
      ~delayLongPress=?,
      ~delayPressIn=?,
      ~delayPressOut=?,
      ~disabled=?,
      ~hitSlop=?,
      ~onLayout=?,
      ~onLongPress=?,
      ~onPress=?,
      ~onPressIn=?,
      ~onPressOut=?,
      ~pressRetentionOffset=?,
      ~style=?,
      ~testID=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      jsProps(
        ~defaultScale?,
        ~activeScale?,
        ~hoverScale?,
        ~focusScale?,
        ~tension?,
        ~friction?,
        ~pressInTension?,
        ~pressInFriction?,
        ~pressOutTension?,
        ~pressOutFriction?,
        ~mouseEnterTension?,
        ~mouseEnterFriction?,
        ~mouseLeaveTension?,
        ~mouseLeaveFriction?,
        ~hoverTension?,
        ~hoverFriction?,
        ~focusTension?,
        ~focusFriction?,
        ~useNativeDriver?,
        /* TouchableWithoutFeedback props */
        ~accessible?,
        ~accessibilityLabel?,
        ~accessibilityComponentType?,
        ~accessibilityTraits?,
        ~delayLongPress?,
        ~delayPressIn?,
        ~delayPressOut?,
        ~disabled?,
        ~hitSlop?,
        ~onLayout?,
        ~onLongPress?,
        ~onPress?,
        ~onPressIn?,
        ~onPressOut?,
        ~pressRetentionOffset?,
        ~style?,
        ~testID?,
        (),
      ),
    children,
  );
