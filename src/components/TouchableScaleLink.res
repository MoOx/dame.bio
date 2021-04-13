open ReactNative

include NativeElement

@module("./TouchableScaleLink.js") @react.component
external make: (
  ~ref: ref=?,
  ~href: // TouchableScaleLink props
  string=?,
  ~activeStyle: Style.t=?,
  ~defaultScale: // TouchableScale props
  float=?,
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
  ~accessible: // TouchableWithoutFeedback props
  bool=?,
  ~accessibilityComponentType: [
    | #none
    | #button
    | #radiobutton_checked
    | #radiobutton_unchecked
  ]=?,
  ~accessibilityElementsHidden: bool=?,
  ~accessibilityHint: string=?,
  ~accessibilityIgnoresInvertColors: bool=?,
  ~accessibilityLabel: string=?,
  ~accessibilityLiveRegion: [#none | #polite | #assertive]=?,
  ~accessibilityRole: [
    | #none
    | #button
    | #link
    | #search
    | #image
    | #keyboardkey
    | #text
    | #adjustable
    | #header
    | #summary
    | #imagebutton
  ]=?,
  ~accessibilityState: Accessibility.state=?,
  ~accessibilityValue: // ~accessibilityTraits: array(AccessibilityTrait.t)=?,
  Accessibility.value=?,
  ~accessibilityViewIsModal: bool=?,
  ~delayLongPress: int=?,
  ~delayPressIn: int=?,
  ~delayPressOut: int=?,
  ~disabled: bool=?,
  ~hitSlop: View.edgeInsets=?,
  ~importantForAccessibility: @string
  [
    | #auto
    | #yes
    | #no
    | @as("no-hide-descendants") #noHideDescendants
  ]=?,
  ~onLayout: Event.layoutEvent => unit=?,
  ~onLongPress: Event.pressEvent => unit=?,
  ~onPress: Event.pressEvent => unit=?,
  ~onPressIn: Event.pressEvent => unit=?,
  ~onPressOut: Event.pressEvent => unit=?,
  ~pressRetentionOffset: View.edgeInsets=?,
  ~testID: string=?,
  ~touchSoundDisabled: bool=?,
  ~children: React.element=?,
  ~rel: // React Native Web Props
  @string
  [
    | #alternate
    | #author
    | @as("dns-prefetch") #dnsPrefetch
    | #icon
    | #license
    | #next
    | #pingback
    | #preconnect
    | #prefetch
    | #preload
    | #prerender
    | #prev
    | #search
    | #stylesheet
  ]=?,
  ~href: string=?,
  ~target: [#_blank | #_self | #_parent | #_top]=?,
) => React.element = "TouchableWithoutFeedback"
