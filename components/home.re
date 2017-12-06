open ReactNative;

let component = ReasonReact.statelessComponent("Home");

type post = {
  id: string,
  title: string
};

let make = (~posts) => {
  ...component,
  render: (_self) =>
    <View>
      <Header />
      <h1> (ReasonReact.stringToElement("Home")) </h1>
      (
        switch (posts: PhenomicPresetReactApp.edge(list(post))) {
        | Inactive
        | Loading =>
          <Text> (ReasonReact.stringToElement("Chargement ...")) </Text>
        | Errored =>
          <Text>
            (ReasonReact.stringToElement("Une erreur est survenue"))
          </Text>
        | Idle(posts) =>
          <ul>
            (
              posts
              |> List.map(
                   (item) =>
                     <li key=item.id>
                       <Link href=("blog/" ++ item.id ++ "/")>
                         (ReasonReact.stringToElement(item.title))
                       </Link>
                     </li>
                 )
              |> Array.of_list
              |> ReasonReact.arrayToElement
            )
          </ul>
        }
      )
      <Footer />
    </View>
};

let jsPostToReason = (jsProps) => {id: jsProps##id, title: jsProps##title};

let jsComponent =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) =>
      make(
        ~posts=
          PhenomicPresetReactApp.jsEdgeToReason(
            jsProps##posts,
            (posts) =>
              posts##list |> Array.map(jsPostToReason) |> Array.to_list
          )
      )
  );

let queries = (_) => {
  let posts =
    PhenomicPresetReactApp.query(
      List({
        path: "posts",
        by: Some("default"),
        value: None,
        order: None,
        limit: None
      })
    );
  {"posts": posts}
};
