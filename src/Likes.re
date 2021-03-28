open Belt;
open Storage;
let get = () => store->likesGet;
let set = lks => {
  store->likesSet(lks);
  saveStore();
};

let isLiked = (id): bool => get()->Array.some(i => i == id);

let like = id => {
  Js.log(("Like", id));
  !isLiked(id)
    ? set(get()->Array.concat([|id|]))
    : Js.log(("Like", id, "already liked"));
};

let unlike = id => {
  Js.log(("Like (un)", id));
  isLiked(id)
    ? set(get()->Array.keep(i => i != id))
    : Js.log(("Like", id, "not liked yet"));
};
