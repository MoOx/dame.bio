let nothing = ReasonReact.null;

let text = ReasonReact.string;

let list = list => list |> Array.of_list |> ReasonReact.array;

let nodeList = node => node##list |> Array.to_list;

module Head = BsReactHelmet;

let localSave = (identifier, value) =>
  Dom.Storage.(localStorage |> setItem(identifier, value));

let localGet = identifier => Dom.Storage.(localStorage |> getItem(identifier));