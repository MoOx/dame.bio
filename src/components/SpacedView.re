open BsReactNative;

let component = ReasonReact.statelessComponent("Spacer");

let space = 20.;

type size =
  | XXL
  | XL
  | L
  | M
  | S
  | XS
  | XXS
  | Custom(float)
  | None;

let make =
    (~vertical=None, ~horizontal=None, ~style=Style.style([]), children) => {
  ...component,
  render: _self =>
    <View
      style={
        Style.concat([
          Style.style(
            switch (vertical) {
            | XXL => [Style.marginVertical(Pt(space *. 4.))]
            | XL => [Style.marginVertical(Pt(space *. 3.))]
            | L => [Style.marginVertical(Pt(space *. 2.))]
            | M => [Style.marginVertical(Pt(space *. 1.))]
            | S => [Style.marginVertical(Pt(space *. 3. /. 4.))]
            | XS => [Style.marginVertical(Pt(space *. 2. /. 4.))]
            | XXS => [Style.marginVertical(Pt(space *. 1. /. 4.))]
            | Custom(value) => [Style.marginVertical(Pt(value))]
            | None => []
            },
          ),
          Style.style(
            switch (horizontal) {
            | XXL => [Style.marginHorizontal(Pt(space *. 4.))]
            | XL => [Style.marginHorizontal(Pt(space *. 3.))]
            | L => [Style.marginHorizontal(Pt(space *. 2.))]
            | M => [Style.marginHorizontal(Pt(space *. 1.))]
            | S => [Style.marginHorizontal(Pt(space *. 3. /. 4.))]
            | XS => [Style.marginHorizontal(Pt(space *. 2. /. 4.))]
            | XXS => [Style.marginHorizontal(Pt(space *. 1. /. 4.))]
            | Custom(value) => [Style.marginHorizontal(Pt(value))]
            | None => []
            },
          ),
          style,
        ])
      }>
      ...children
    </View>,
};
