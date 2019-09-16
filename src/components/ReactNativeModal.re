open ReactNative;
include NativeElement;

module Orientation = Modal_Orientation;
module OrientationChange = Modal_OrientationChange;

[@react.component] [@bs.module "modal-enhanced-react-native-web"]
external make:
  (
    ~ref: ref=?,
    // animationIn	string or object	'slideInUp'	Modal show animation
    // animationInTiming	number	300	Timing for the modal show animation (in ms)
    // animationOut	string or object	'slideOutDown'	Modal hide animation
    // animationOutTiming	number	300	Timing for the modal hide animation (in ms)
    // avoidKeyboard	bool	false	Move the modal up if the keyboard is open
    // coverScreen	bool	true	Will use RN Modal component to cover the entire screen wherever the modal is mounted in the component hierarchy
    ~hasBackdrop: bool=?,
    // backdropColor	string	'black'	The backdrop background color
    // backdropOpacity	number	0.70	The backdrop opacity when the modal is visible
    // backdropTransitionInTiming	number	300	The backdrop show timing (in ms)
    // backdropTransitionOutTiming	number	300	The backdrop hide timing (in ms)
    // customBackdrop	node	null	The custom backdrop element
    // children	node	REQUIRED	The modal content
    // deviceHeight	number	null	Device height (useful on devices that can hide the navigation bar)
    // deviceWidth	number	null	Device width (useful on devices that can hide the navigation bar)
    ~isVisible: bool,
    // onBackButtonPress	func	() => null	Called when the Android back button is pressed
    ~onBackdropPress: unit => unit,
    // onModalWillHide	func	() => null	Called before the modal hide animation begins
    // onModalHide	func	() => null	Called when the modal is completely hidden
    // onModalWillShow	func	() => null	Called before the modal show animation begins
    // onModalShow	func	() => null	Called when the modal is completely visible
    // onSwipeStart	func	() => null	Called when the swipe action started
    // onSwipeMove	func	(percentageShown) => null	Called on each swipe event
    // onSwipeComplete	func	({ swipingDirection }) => null	Called when the swipeThreshold has been reached
    // onSwipeCancel	func	() => null	Called when the swipeThreshold has not been reached
    // scrollOffset	number	0	When > 0, disables swipe-to-close, in order to implement scrollable content
    // scrollOffsetMax	number	0	Used to implement overscroll feel when content is scrollable. See /example directory
    // scrollTo	func	null	Used to implement scrollable modal. See /example directory for reference on how to use it
    // scrollHorizontal	bool	false	Set to true if your scrollView is horizontal (for a correct scroll handling)
    // swipeThreshold	number	100	Swiping threshold that when reached calls onSwipeComplete
    // swipeDirection	string or array	null	Defines the direction where the modal can be swiped. Can be 'up', 'down', 'left, or 'right', or a combination of them like ['up','down']
    // useNativeDriver	bool	false	Defines if animations should use native driver
    // hideModalContentWhileAnimating	bool	false	Enhances the performance by hiding the modal content until the animations complete
    // propagateSwipe	bool	false	Allows swipe events to propagate to children components (eg a ScrollView inside a modal)
    // style	any	null	Style applied to the modal
    // Modal props
    ~animationType: [@bs.string] [ | `none | `slide | `fade]=?,
    ~hardwareAccelerated: bool=?,
    ~onDismiss: unit => unit=?,
    ~onOrientationChange: Event.syntheticEvent({
                            .
                            "orientation": OrientationChange.t,
                          }) =>
                          unit
                            =?,
    ~onRequestClose: unit => unit=?,
    ~onShow: unit => unit=?,
    ~presentationStyle: [@bs.string] [
                          | `fullScreen
                          | `pageSheet
                          | `formSheet
                          | `overFullScreen
                        ]
                          =?,
    ~supportedOrientations: array(Orientation.t)=?,
    ~transparent: bool=?,
    ~visible: bool=?,
    ~children: React.element=?
  ) =>
  React.element =
  "default";
