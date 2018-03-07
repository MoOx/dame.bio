/*
 type post = {
   id: string,
   title: string,
   tags: list(string),
   body: PhenomicPresetReactApp.BodyRenderer.jsBody
 };
 */
type mediaSize = {source_url: string};

let decodeMediaSize = json : mediaSize =>
  Json.Decode.{source_url: json |> field("source_url", string)};

type mediaSizes = {
  thumbnail: mediaSize,
  medium: mediaSize,
  large: mediaSize
};

let decodeMediaSizes = json : mediaSizes =>
  Json.Decode.{
    thumbnail: json |> field("thumbnail", decodeMediaSize),
    medium: json |> field("medium", decodeMediaSize),
    large: json |> field("large", decodeMediaSize)
  };

type mediaDetails = {
  width: int,
  height: int,
  sizes: mediaSizes
};

let decodeMediaDetails = json : mediaDetails =>
  Json.Decode.{
    width: json |> field("width", int),
    height: json |> field("height", int),
    sizes: json |> field("sizes", decodeMediaSizes)
  };

type media = {media_details: mediaDetails};

let decodeMedia = json : media =>
  Json.Decode.{
    media_details: json |> field("media_details", decodeMediaDetails)
  };

type term = {
  id: int,
  slug: string,
  name: string,
  taxonomy: string,
  hasParent: bool
};

let decodeHasParent = json : bool => {
  let links = Js.Json.decodeObject(json);
  switch links {
  | Some(somelinks) =>
    /* links[0] == somelinks */
    [%raw {|Boolean(links[0].up)|}]
  | None => false
  };
};

let decodeTerm = json : term =>
  Json.Decode.{
    id: json |> field("id", int),
    slug: json |> field("slug", string),
    name: json |> field("name", string),
    taxonomy: json |> field("taxonomy", string),
    hasParent: json |> field("_links", decodeHasParent)
  };

type terms = {
  categories: list(term),
  tags: list(term)
};

let decodeTerms = json : terms => {
  let termsArray = Js.Json.decodeArray(json);
  switch termsArray {
  | Some(termsArray) => {
      categories:
        Json.Decode.(termsArray[0] |> array(decodeTerm)) |> Array.to_list,
      tags: Json.Decode.(termsArray[1] |> array(decodeTerm)) |> Array.to_list
    }
  | None => {categories: [], tags: []}
  };
};

type post = {
  id: int,
  date: string,
  slug: string,
  title: string,
  featuredMedia: list(media),
  terms
};

let decodeFeaturedMedia = json : list(media) =>
  Json.Decode.(json |> array(decodeMedia)) |> Array.to_list;

let decodePost = json : post =>
  Json.Decode.{
    id: json |> field("id", int),
    date: json |> field("date", string),
    slug: json |> field("slug", string),
    title: json |> at(["title", "rendered"], string),
    featuredMedia:
      json |> at(["_embedded", "wp:featuredmedia"], decodeFeaturedMedia),
    terms: json |> at(["_embedded", "wp:term"], decodeTerms)
  };

let decodePosts = json : list(post) =>
  Json.Decode.(json |> array(decodePost)) |> Array.to_list;
/* let doNothing = (a) => a; */
/* type postEdge = PhenomicPresetReactApp.edge(post); */
/* let jsPostToReason = (jsProps) => {
     id: jsProps##id,
     title: jsProps##title,
     tags: jsProps##tags,
     body: jsProps##body
   }; */
/* let jsPost = (jsPost) =>
   PhenomicPresetReactApp.jsEdgeToReason(jsPost, doNothing); */
/* type postsEdge = PhenomicPresetReactApp.edge(list(post)); */
/* let jsPostsToReason = (posts) =>
   posts##list |> Array.map(jsPostToReason) |> Array.to_list; */
/* let jsPosts = (jsPosts) =>
   PhenomicPresetReactApp.jsEdgeToReason(jsPosts, jsPostsToReason); */
