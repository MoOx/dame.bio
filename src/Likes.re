let get = () => Storage.(getStore()->likesGet);
let set = lks => {
  open Storage;
  let store = getStore();
  store->likesSet(lks);
  store->saveStore;
};

let isLiked = id: bool =>
  get()
  ->Belt.Array.some(i => {
      Js.log3(i, id, i == id);
      i == id;
    });

let like = id =>
  !isLiked(id) ?
    set(get()->Belt.Array.concat([|id|])) : Js.log2(id, "already liked");

let unlike = id =>
  isLiked(id) ?
    set(get()->Belt.Array.keep(i => i != id)) : Js.log2(id, "not liked yet");
