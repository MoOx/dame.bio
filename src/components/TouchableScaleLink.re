open ReactNative;

include NativeElement;

[@bs.module "./TouchableScaleLink.js"] [@react.component]
external make:
  (
    ~ref: ref=?,
    // TouchableScaleLink props
    ~href: string=?,
    ~activeStyle: Style.t=?,
    // TouchableScale props
    ~defaultScale: float=?,
    ~activeScale: float=?,
    ~hoverScale: float=?,
    ~focusScale: float=?,
    ~tension: float=?,
    ~friction: float=?,
    ~pressInTension: float=?,
    ~pressInFriction: float=?,
    ~pressOutTension: float=?,
    ~pressOutFriction: float=?,
    ~mouseEnterTension: float=?,
    ~mouseEnterFriction: float=?,
    ~mouseLeaveTension: float=?,
    ~mouseLeaveFriction: float=?,
    ~hoverTension: float=?,
    ~hoverFriction: float=?,
    ~focusTension: float=?,
    ~focusFriction: float=?,
    ~useNativeDriver: bool=?,
    ~style: Style.t=?,
    // TouchableWithoutFeedback props
    ~accessible: bool=?,
    ~accessibilityComponentType: [@bs.string] [
                                   | `none
                                   | `button
                                   | `radiobutton_checked
                                   | `radiobutton_unchecked
                                 ]
                                   =?,
    ~accessibilityHint: string=?,
    ~accessibilityIgnoresInvertColors: bool=?,
    ~accessibilityLabel: string=?,
    ~accessibilityRole: [@bs.string] [
                          | `none
                          | `button
                          | `link
                          | `search
                          | `image
                          | `keyboardkey
                          | `text
                          | `adjustable
                          | `header
                          | `summary
                          | `imagebutton
                        ]
                          =?,
    ~accessibilityStates: array(AccessibilityState.t)=?,
    ~accessibilityTraits: array(AccessibilityTrait.t)=?,
    ~delayLongPress: int=?,
    ~delayPressIn: int=?,
    ~delayPressOut: int=?,
    ~disabled: bool=?,
    ~hitSlop: Types.edgeInsets=?,
    ~onBlur: Event.targetEvent => unit=?,
    ~onFocus: Event.targetEvent => unit=?,
    ~onLayout: Event.layoutEvent => unit=?,
    ~onLongPress: Event.pressEvent => unit=?,
    ~onPress: Event.pressEvent => unit=?,
    ~onPressIn: Event.pressEvent => unit=?,
    ~onPressOut: Event.pressEvent => unit=?,
    ~pressRetentionOffset: Types.edgeInsets=?,
    ~testID: string=?,
    ~children: React.element=?
  ) =>
  React.element =
  "TouchableWithoutFeedback";
