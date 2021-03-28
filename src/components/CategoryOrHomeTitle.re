open Belt;

[@react.component]
let make =
    (
      ~categories:
         option(
           WPGraphQL.GetPagesAndPosts.GetPagesAndPosts_inner.t_categories,
         ),
      ~generalSettings:
         option(WPGraphQL.GetGlobals.GetGlobals_inner.t_generalSettings),
    ) => {
  <>
    {categories
     ->Option.flatMap(p => p.nodes)
     ->Option.flatMap(nodes => nodes[0])
     ->Option.flatMap(node => node)
     ->Option.flatMap(node =>
         node.description->Option.isSome
           ? node.description : node.name->Option.isSome ? node.name : None
       )
     ->Option.map(title =>
         <Next.Head> <title> title->React.string </title> </Next.Head>
       )
     ->Option.getWithDefault(
         generalSettings
         ->Option.flatMap(node => node.description)
         ->Option.map(title =>
             <Next.Head> <title> title->React.string </title> </Next.Head>
           )
         ->Option.getWithDefault(React.null),
       )}
  </>;
};
