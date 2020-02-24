open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container": viewStyle(~display=`flex, ()),
      "image": imageStyle(~flexGrow=1., ()),
      "children":
        textStyle(
          ~zIndex=1,
          ~fontWeight=`bold,
          ~fontSize=24.,
          ~color="#fff",
          (),
        ),
    })
  );

let uri = "/images/banner-button.png";

[@react.component]
let make =
    (
      ~href,
      ~children,
      ~verticalSpace as vertical=SpacedView.S,
      ~horizontalSpace as horizontal=SpacedView.L,
      (),
    ) => {
  <ViewLink href style=styles##container>
    <ImageBackgroundFromUri style=styles##image resizeMode=`stretch uri>
      <SpacedView vertical horizontal>
        <Text style=styles##children> children </Text>
      </SpacedView>
    </ImageBackgroundFromUri>
  </ViewLink>;
};
