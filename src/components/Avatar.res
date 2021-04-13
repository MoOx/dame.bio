open Belt
open ReactNative

let styles = {
  open Style
  StyleSheet.create({
    "avatar": style(~width=40.->dp, ~height=40.->dp, ~borderRadius=Consts.Radius.avatar, ()),
    "avatarEmpty": style(
      ~lineHeight=62.,
      ~color="#fff",
      ~textAlign=#center,
      ~fontWeight=#_300,
      ~fontSize=50.,
      ~fontFamily="Georgia",
      (),
    ),
    "avatarDefault": style(
      ~color="#fff",
      ~textAlign=#center,
      ~fontWeight=#_600,
      ~fontSize=24.,
      ~lineHeight=40.,
      (),
    ),
    "avatarImage": style(
      ~position=#absolute,
      ~top=0.->dp,
      ~left=0.->dp,
      ~width=40.->dp,
      ~height=40.->dp,
      ~borderRadius=Consts.Radius.avatar,
      (),
    ),
  })
}
let notSoRandomColor = s => {
  let hue = mod(
    List.makeBy(String.length(s), i => String.get(s, i))->List.reduce(0, (hue, char) =>
      hue + Char.code(char)
    ),
    360,
  )
  "hsl(" ++ (string_of_int(hue) ++ ", 90%, 95%)")
}

@react.component
let make = (~name=?, ~url=?, ()) =>
  <View
    style={
      open Style
      arrayOption([
        Some(styles["avatar"]),
        name->Option.map(name => style(~backgroundColor=notSoRandomColor(name), ())),
      ])
    }>
    {switch name {
    | Some(name) if String.length(name) > 1 =>
      <Text style={styles["avatarDefault"]}>
        {String.sub(name, 0, 1)->String.capitalize_ascii->React.string}
      </Text>
    | _ => <Text style={styles["avatarEmpty"]}> {j`¨̮`->React.string} </Text>
    }}
    {switch url {
    | Some(url) =>
      <ImageFromUri style={styles["avatarImage"]} resizeMode=#contain uri=url ssr=false />
    | None => React.null
    }}
  </View>
