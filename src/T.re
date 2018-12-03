let getMainCategory = (categoriesNodes: array(option('a))): 'a =>
  categoriesNodes
  ->Belt.Array.keepMap(x =>
      x->Belt.Option.flatMap(cat =>
        cat##parent->Belt.Option.isNone ? Some(cat) : None
      )
    )
  ->Belt.Array.get(0)
  ->Belt.Option.getWithDefault({
      "name": Some(""),
      "slug": Some("non-classe"),
      "parent": Some({"id": ""}),
    });
