open ReactNative

@react.component
let make = (
  ~value,
  ~style as s,
  ~placeholder,
  ~onFocus=?,
  ~onChangeText,
  ~minHeight as minH=40.,
  (),
) => {
  let (height, setHeight) = React.useState(() => 0.)
  <TextInput
    multiline=true
    onContentSizeChange={/* native only https://github.com/necolas/react-native-web/issues/793 */
    (event: TextInput.contentSizeChangeEvent) => {
      let height = event.nativeEvent.contentSize.height
      setHeight(_ => height)
    }}
    onChange={_ =>
      if Platform.os === Platform.web {
        /* https://github.com/necolas/react-native-web/issues/793#issuecomment-437549351 */
        let event = %raw("arguments[0]")
        let height = event["nativeEvent"]["srcElement"]["scrollHeight"]
        setHeight(_ => height)
      }}
    style={
      open Style
      array([s, style(~height=dp(max(minH, height)), ())])
    }
    value
    placeholder
    onChangeText
    ?onFocus
  />
}
