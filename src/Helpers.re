let apiBaseUrl = "https://dame.bio/";

let nothing = ReasonReact.null;

let text = ReasonReact.string;

let list = list => list |> Array.of_list |> ReasonReact.array;

let nodeList = node => node##list |> Array.to_list;

module Head = BsReactHelmet;

let localSave = (identifier, value) =>
  Dom.Storage.(localStorage |> setItem(identifier, value));

let localGet = identifier =>
  Dom.Storage.(localStorage |> getItem(identifier));

let stringMapPartial = (f, s) => {
  let b = Buffer.create(String.length(s));
  let addPerhaps = c =>
    switch (f(c)) {
    | None => ()
    | Some(c') => Buffer.add_char(b, c')
    };

  String.iter(addPerhaps, s);
  Buffer.contents(b);
};

let tagifyChar = (c) =>
  switch (c) {
  | ' ' => None
  | _ => Some(c)
  };

let tagifyString = (string) => stringMapPartial(tagifyChar, string);