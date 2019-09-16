let saveIt = (identifier, value) =>
  switch (Env.getPlatform()) {
  | Browser =>
    Dom.Storage.(localStorage |> setItem(identifier, value));
    ();
  | _ => ()
  };

let getIt = identifier =>
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
  mutable authToken: option(string),
  mutable refreshToken: option(string),
};

let freshStore = () =>
  store(
    ~name="",
    ~email="",
    ~url="",
    ~likes=[||],
    ~authToken=None,
    ~refreshToken=None,
  );

let store =
  switch (getIt("dame.bio")) {
  | Some(serializedStore) =>
    try (Js.Json.parseExn(serializedStore)->Obj.magic) {
    | exn =>
      Js.log2("Failed to parse store", exn);
      freshStore();
    }
  | None => freshStore()
  };

let cleanStore = () => {
  store->nameSet("");
  store->emailSet("");
  store->urlSet("");
  store->likesSet([||]);
  store->authTokenSet(None);
  store->refreshTokenSet(None);
};

let saveStore = (): unit =>
  saveIt("dame.bio", Js.Json.stringify(store->Obj.magic));
