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
}

let decodeComment = (json): comment => {
  open Json.Decode
  {
    type_: json |> field("type", string),
    id: json |> field("id", int),
    parent: json |> field("parent", int),
    author: json |> field("author", int),
    author_name: json |> field("author_name", string),
    author_url: json |> field("author_url", string),
    author_avatar_url: json |> at(list{"author_avatar_urls", "96"}, string),
    date: json |> field("date_gmt", string),
    content: json |> at(list{"content", "rendered"}, string),
  }
}

let decodeComments = (json): list<comment> =>
  {
    open Json.Decode
    json |> array(decodeComment)
  } |> Belt.List.fromArray

let decodePartialComments = (json): list<comment> =>
  {
    open Json.Decode
    Belt.Array.getUnsafe(Obj.magic(json), 0) |> array(decodeComment)
  } |> Belt.List.fromArray

type comments = list<comment>
