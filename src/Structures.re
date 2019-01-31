type mediaSize = {source_url: string};

let decodeMediaSize = (json): mediaSize =>
  Json.Decode.{source_url: json |> field("source_url", string)};

type mediaSizes = {
  /* thumbnail: mediaSize, */
  medium: mediaSize,
  /* large: mediaSize, */
};

type mediaDetails = {
  /* width: int,
     height: int, */
  sizes: mediaSizes,
};

type media = {media_details: mediaDetails};

let decodeMedia = (json): media =>
  Json.Decode.{
    media_details:
      json
      |> field("media_details", (json) =>
           (
             {
               /* width: json |> field("width", int),
                  height: json |> field("height", int), */
               sizes:
                 json
                 |> field("sizes", json =>
                      {
                        /* thumbnail: json |> field("thumbnail", decodeMediaSize), */
                        medium: json |> field("medium", decodeMediaSize),
                        /* large: json |> field("large", decodeMediaSize), */
                      }
                    ),
             }: mediaDetails
           )
         ),
  };

type term = {
  id: int,
  slug: string,
  name: string,
  taxonomy: string,
  hasParent: bool,
};

let decodeTerm = (json): term =>
  Json.Decode.{
    id: json |> field("id", int),
    slug: json |> field("slug", string),
    name: json |> field("name", string),
    taxonomy: json |> field("taxonomy", string),
    hasParent:
      json
      |> field("_links", (json) =>
           (
             {
               let links = Js.Json.decodeObject(json);
               switch (links) {
               | Some(_) =>
                 %raw
                 {|Boolean(links.up)|}
               | None => false
               };
             }: bool
           )
         ),
  };

type terms = {
  categories: list(term),
  tags: list(term),
};

let decodeTerms = (json): terms => {
  let termsArray = Js.Json.decodeArray(json);
  switch (termsArray) {
  | Some(termsArray) => {
      categories:
        Json.Decode.(termsArray[0] |> array(decodeTerm))
        |> Belt.List.fromArray,
      tags:
        Json.Decode.(termsArray[1] |> array(decodeTerm))
        |> Belt.List.fromArray,
    }
  | None => {categories: [], tags: []}
  };
};

type comment = {
  type_: string,
  id: int,
  parent: int,
  author: int,
  author_name: string,
  author_url: string,
  author_avatar_url: string,
  date: string,
  content: string,
};

let decodeComment = (json): comment =>
  Json.Decode.{
    type_: json |> field("type", string),
    id: json |> field("id", int),
    parent: json |> field("parent", int),
    author: json |> field("author", int),
    author_name: json |> field("author_name", string),
    author_url: json |> field("author_url", string),
    author_avatar_url: json |> at(["author_avatar_urls", "96"], string),
    date: json |> field("date_gmt", string),
    content: json |> at(["content", "rendered"], string),
  };

let decodeComments = (json): list(comment) =>
  Json.Decode.(json |> array(decodeComment)) |> Belt.List.fromArray;

let decodePartialComments = (json): list(comment) =>
  Json.Decode.(
    Belt.Array.getUnsafe(Obj.magic(json), 0) |> array(decodeComment)
  )
  |> Belt.List.fromArray;

type comments = list(comment);

type post = {
  id: int,
  date: string,
  slug: string,
  title: string,
  contentHTML: string,
  featuredMedia: list(media),
  comments: option(comments),
  likes: int,
  terms,
};

let decodePost = (json): post =>
  Json.Decode.{
    id: json |> field("id", int),
    date: json |> field("date_gmt", string),
    slug: json |> field("slug", string),
    title: json |> at(["title", "rendered"], string),
    contentHTML: json |> at(["content", "rendered"], string),
    comments:
      json |> optional(at(["_embedded", "replies"], decodePartialComments)),
    featuredMedia:
      json
      |> at(["_embedded", "wp:featuredmedia"], json =>
           json |> array(decodeMedia) |> Belt.List.fromArray
         ),
    likes: 0,
    terms: json |> at(["_embedded", "wp:term"], decodeTerms),
  };

let decodePosts = (json): list(post) =>
  Json.Decode.(json |> array(decodePost)) |> Belt.List.fromArray;

let decodeRelatedPosts = (json): list(post) => {
  Json.Decode.(
    json
    |> field("rendered", string)
    /* remove shit injected by the "related posts plugin" */
    |> Js.String.replaceByRe(
         [%re "/^<div class=\\\"rpbt_wp_rest_api\\\">\\n/"],
         "",
       )
    |> Js.String.replaceByRe([%re "/\\n<\\/div>$/"], "")
    |> Json.parseOrRaise
    |> decodePosts
  );
};

let findRootCategory = (item: post): term =>
  switch (
    Belt.List.getBy(item.terms.categories, (term: term) => !term.hasParent)
  ) {
  | Some(term) => term
  | None =>
    switch (Belt.List.head(item.terms.categories)) {
    | Some(term) => term
    | None => {
        id: 0,
        slug: "non-classe",
        name: "",
        taxonomy: "",
        hasParent: false,
      }
    }
  };

let placeholderPost = (id): post => {
  id,
  date: "",
  slug: "",
  title: " ",
  contentHTML: "",
  featuredMedia: [{
                    media_details: {
                      sizes: {
                        medium: {
                          source_url: "",
                        },
                      },
                    },
                  }],
  comments: None,
  likes: 0,
  terms: {
    categories: [],
    tags: [],
  },
};
