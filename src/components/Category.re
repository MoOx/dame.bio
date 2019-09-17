open Belt;

type t = [
  | `permaculture
  | `alimentation
  | `bienEtre
  | `lifestyle
  | `default
];

let from = category =>
  category
  ->Option.map(c =>
      switch (c##slug) {
      | Some("permaculture") => `permaculture
      | Some("alimentation") => `alimentation
      | Some("bien-etre") => `bienEtre
      | Some("lifestyle") => `lifestyle
      | _ => `default
      }
    )
  ->Option.getWithDefault(`default);

let toSlug =
  fun
  | `permaculture => "permaculture"
  | `alimentation => "alimentation"
  | `bienEtre => "bienEtre"
  | `lifestyle => "lifestyle"
  | `default => "default";
