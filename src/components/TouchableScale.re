[@bs.module "../../../../src/components/TouchableScale.js"]
external reactClass: ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type jsProps = {
  [@bs.optional]
  style: BsReactNative.Style.t,
  [@bs.optional]
  defaultScale: float,
  [@bs.optional]
  activeScale: float,
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
  useNativeDriver: bool,
};

let make =
    (
      ~style=?,
      ~defaultScale=?,
      ~activeScale=?,
      ~tension=?,
      ~friction=?,
      ~pressInTension=?,
      ~pressInFriction=?,
      ~pressOutTension=?,
      ~pressOutFriction=?,
      ~useNativeDriver=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      jsProps(
        ~style?,
        ~defaultScale?,
        ~activeScale?,
        ~tension?,
        ~friction?,
        ~pressInTension?,
        ~pressInFriction?,
        ~pressOutTension?,
        ~pressOutFriction?,
        ~useNativeDriver?,
        (),
      ),
    children,
  );
