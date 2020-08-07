open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "wrapper":
        style(
          ~flexGrow=1.,
          // flexShrink(1.),
          ~width=100.->pct,
          // overflow(Hidden),
          ~alignItems=`center,
          ~backgroundColor="#fefefe",
          (),
        ),
      "container":
        style(
          ~flexDirection=`row,
          ~flexWrap=`wrap,
          ~justifyContent=`center,
          ~flexGrow=1.,
          ~flexShrink=1.,
          ~width=100.->pct,
          ~maxWidth=1200.->dp,
          (),
        ),
    })
  );

[@react.component]
let make = (~wrapperStyle=?, ~style as s=?, ~children, ()) => {
  <View style=Style.(arrayOption([|Some(styles##wrapper), wrapperStyle|]))>
    <View style=Style.(arrayOption([|Some(styles##container), s|]))>
      children
    </View>
  </View>;
};
