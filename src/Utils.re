open Belt;

[@bs.module]
external fetchJsonp: string => Js.Promise.t(Fetch.Response.t) = "fetch-jsonp";

[@bs.val] external encodeURIComponent: string => string = "";

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
  ->Js.String.replace(
      "href=\"" ++ Consts.backendUrl ++ "/",
      "href=\"" ++ Consts.frontendUrl ++ "/",
      _,
    )
  ->Js.String.replaceByRe(
      [%re "/=\"\\/wp-content/g"],
      "=\"" ++ Consts.backendUrl ++ "/wp-content",
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

let rootCategory = item =>
  item##categories
  ->Option.flatMap(categories => categories##nodes)
  ->Option.map(nodes => nodes->Array.keepMap(node => node))
  ->Option.flatMap(categoriesNodes => categoriesNodes[0]);

let catHref = cat =>
  "/"
  ++ cat
     ->Option.flatMap(cat => cat##slug)
     ->Option.getWithDefault("_")
     ->encodeURI
  ++ "/";

let postHref = item =>
  item->rootCategory->catHref
  ++ item##slug->Option.getWithDefault(item##id)
  ++ "/";
