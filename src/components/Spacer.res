open ReactNative

let space = 20.

type size =
  | XXL
  | XL
  | L
  | M
  | S
  | XS
  | XXS
  | Custom(float)

let size = x =>
  switch x {
  | XXL => space *. 4.
  | XL => space *. 3.
  | L => space *. 2.
  | M => space *. 1.
  | S => space *. 3. /. 4.
  | XS => space *. 2. /. 4.
  | XXS => space *. 1. /. 4.
  | Custom(value) => value
  }

let makeStyle = s => {
  open Style
  style(~width=dp(s), ~height=dp(s), ())
}

let styles = StyleSheet.create({
  "xxl": makeStyle(XXL->size),
  "xl": makeStyle(XL->size),
  "l": makeStyle(L->size),
  "m": makeStyle(M->size),
  "s": makeStyle(S->size),
  "xs": makeStyle(XS->size),
  "xxs": makeStyle(XXS->size),
})

@react.component
let make = (~size: size=M, ~style as styl=?, ()) =>
  <View
    style={
      open Style
      arrayOption([
        Some(
          switch size {
          | XXL => styles["xxl"]
          | XL => styles["xl"]
          | L => styles["l"]
          | M => styles["m"]
          | S => styles["s"]
          | XS => styles["xs"]
          | XXS => styles["xxs"]
          | Custom(value) => makeStyle(value)
          },
        ),
        styl,
      ])
    }
  />