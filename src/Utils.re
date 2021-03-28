open Belt;

[@bs.module]
external fetchJsonp: string => Js.Promise.t(Fetch.Response.t) = "fetch-jsonp";

[@bs.val] external encodeURIComponent: string => string = "encodeURIComponent";

let encodeURI = uri => encodeURIComponent(uri);

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

let tagifyChar = c =>
  switch (c) {
  | ' ' => None
  | _ => Some(c)
  };

let tagifyString = string => stringMapPartial(tagifyChar, string);

/* make images url absolute */
let adjustUrls = s =>
  s
  // remove domains
  ->Js.String.replaceByRe(
      [%re "/href=\"https:\\/\\/(data\\.)?dame\\.bio\\//g"],
      "href=\"/",
      _,
    )
  // enforce internal links to have trailing slash
  ->Js.String.replaceByRe([%re "/href=\"\\/([^\"]+)/g"], "href=\"/$1/", _)
  // enforce internal links to have trailing slash, and ONLY one, cause the rules above can duplicated them
  ->Js.String.replaceByRe(
      [%re "/href=\"\\/([^\"]+)\\/\\//g"],
      "href=\"/$1/",
      _,
    )
  // re-force wordpress href/src to point to the right place
  ->Js.String.replaceByRe(
      [%re "/=\"\\/wp-content/g"],
      "=\"" ++ Consts.backendUrl ++ "/wp-content",
      _,
    )
  // legacy urls inside posts
  // @todo, change in database
  // also check public/_redirects
  ->Js.String.replaceByRe(
      [%re "/href=\"\\/recettes\\//g"],
      "href=\"/alimentation/",
      _,
    )
  ->Js.String.replaceByRe(
      [%re "/href=\"\\/ecologie\\//g"],
      "href=\"/permaculture/",
      _,
    );

let frenchDate = (date: option(string)) => {
  date
  ->Option.flatMap(d =>
      d
      ->Js.String.replace(" ", "T", _) // legacy fixup, in case...
      ->Js.String.split("T", _)[0]
      ->Option.map(date => {
          let parts = date->Js.String.split("-", _);
          parts[2]->Option.getWithDefault("")
          ++ "/"
          ++ parts[1]->Option.getWithDefault("")
          ++ "/"
          ++ parts[0]->Option.getWithDefault("");
        })
    )
  ->Option.getWithDefault("");
};
