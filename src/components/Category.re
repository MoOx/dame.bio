type t = [
  | `permaculture
  | `alimentation
  | `bienEtre
  | `lifestyle
  | `default
];

let from = categorySlug =>
  switch (categorySlug) {
  | Some("permaculture") => `permaculture
  | Some("alimentation") => `alimentation
  | Some("bien-etre") => `bienEtre
  | Some("lifestyle") => `lifestyle
  | _ => `default
  };

let toSlug =
  fun
  | `permaculture => "permaculture"
  | `alimentation => "alimentation"
  | `bienEtre => "bienEtre"
  | `lifestyle => "lifestyle"
  | `default => "default";
