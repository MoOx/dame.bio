@val external window: 'a = "window"

type platform =
  | Browser
  | Node

let getPlatform = () =>
  if Js.typeof(window) !== "undefined" {
    Browser
  } else {
    Node
  }
