let save = (identifier, value) =>
  switch (Env.getPlatform()) {
  | Browser => Dom.Storage.(localStorage |> setItem(identifier, value))
  | _ => ()
  };

let get = identifier =>
  switch (Env.getPlatform()) {
  | Browser => Dom.Storage.(localStorage |> getItem(identifier))
  | _ => None
  };

[@bs.deriving abstract]
type store = {
  mutable name: string,
  mutable email: string,
  mutable url: string,
  mutable likes: array(string),
};

let freshStore = () => store(~name="", ~email="", ~url="", ~likes=[||]);

let getStore = () =>
  switch (get("dame.bio")) {
  | Some(serializedStore) =>
    try (Js.Json.parseExn(serializedStore)->Obj.magic) {
    | exn =>
      Js.log2("Failed to parse store", exn);
      freshStore();
    }
  | None => freshStore()
  };

let saveStore = (store: store): unit => {
  save("dame.bio", Js.Json.stringify(store->Obj.magic));
  ();
};
