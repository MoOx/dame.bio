open ReactNative

let styles = {
  open Style
  StyleSheet.create({
    "container": style(~justifyContent=#center, ~alignItems=#center, ()),
    "oops": style(~fontSize=64., ~lineHeight=64., ~color="#ddd", ()),
    "title": style(~margin=60.->dp, ~fontSize=24., ~lineHeight=48., ~textAlign=#center, ()),
  })
}

@react.component
let make = (~label, ()) => {
  let errorText = switch label {
  | None => "Une erreur est survenue"
  | Some(label) => label
  }
  <SpacedView vertical=XXL horizontal=None>
    <Text style={styles["oops"]}> {"Ouuuups!"->React.string} </Text>
    <View> <Text style={styles["title"]}> {errorText->React.string} </Text> </View>
  </SpacedView>
  /*
   {status === 404 && (
     <View>
       <Text>
         {"It seems you found a broken link. "}
         {"Sorry about that. "}
         <br />
         {"Do not hesitate to report this page."}
       </Text>
     </View>
   )}
 */
}
