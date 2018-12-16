open Storage;
let get = () => store->likesGet;
let set = lks => {
  store->likesSet(lks);
  saveStore();
};

let isLiked = (id): bool => get()->Belt.Array.some(i => i == id);

let like = id =>
  !isLiked(id) ?
    set(get()->Belt.Array.concat([|id|])) : Js.log2(id, "already liked");

let unlike = id =>
  isLiked(id) ?
    set(get()->Belt.Array.keep(i => i != id)) : Js.log2(id, "not liked yet");
