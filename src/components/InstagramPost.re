open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "block":
        style(
          ~position=`relative,
          ~flex=1.,
          ~backgroundColor=Consts.Colors.lightGrey,
          (),
        ),
      "image": style(~position=`relative, ~flex=1., ()),
    })
  );

[@react.component]
let make = (~item, ~size, ()) => {
  let uri = item##images##standard_resolution##url;
  <ViewLink
    href=item##link
    style=Style.(
      array([|styles##block, style(~width=size->dp, ~height=size->dp, ())|])
    )>
    <ImageFromUri style=styles##image uri />
  </ViewLink>;
};
