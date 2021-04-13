open ReactNative

let styles = {
  open Style
  StyleSheet.create({
    "title": style(~fontSize=28., ~lineHeight=28. *. 1.5, ~color="#006579", ~fontWeight=#_300, ()),
  })
}

@react.component
let make = (~children) => <Text style={styles["title"]}> children </Text>
