open Belt

@module
external fetchJsonp: string => Js.Promise.t<Fetch.Response.t> = "fetch-jsonp"

@val external encodeURIComponent: string => string = "encodeURIComponent"

let encodeURI = uri => encodeURIComponent(uri)

let stringMapPartial = (f, s) => {
  let b = Buffer.create(String.length(s))
  let addPerhaps = c =>
    switch f(c) {
    | None => ()
    | Some(c') => Buffer.add_char(b, c')
    }

  String.iter(addPerhaps, s)
  Buffer.contents(b)
}

let tagifyChar = c =>
  switch c {
  | ' ' => None
  | _ => Some(c)
  }

let tagifyString = string => stringMapPartial(tagifyChar, string)

/* make images url absolute */
let adjustUrls = s =>
  s
  // remove domains
  ->Js.String2.replaceByRe(%re("/href=\"https:\\/\\/(data\\.)?dame\\.bio\\//g"), "href=\"/")
  // enforce internal links to have no trailing slash
  ->Js.String2.replaceByRe(%re("/href=\"\\/([^\"]+)\//g"), "href=\"/$1")
  // re-force wordpress href/src to point to the right place
  ->Js.String2.replaceByRe(
    %re("/=\"\\/wp-content/g"),
    "=\"" ++ (Consts.backendUrl ++ "/wp-content"),
  )
  ->// legacy urls inside posts
  // @todo, change in database
  // also check public/_redirects
  Js.String2.replaceByRe(%re("/href=\"\\/recettes\\//g"), "href=\"/alimentation/")
  ->Js.String2.replaceByRe(%re("/href=\"\\/ecologie\\//g"), "href=\"/permaculture/")

let frenchDate = (date: option<string>) =>
  date
  ->Option.flatMap(d =>
    (d->Js.String2.replace(" ", "T")->Js.String2.split("T"))[0]->Option.map(date => {
      let parts = date->Js.String2.split("-")
      parts[2]->Option.getWithDefault("") ++
        ("/" ++
        (parts[1]->Option.getWithDefault("") ++ ("/" ++ parts[0]->Option.getWithDefault(""))))
    })
  )
  ->Option.getWithDefault("")
