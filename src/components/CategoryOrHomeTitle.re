open Belt;

let component = ReasonReact.statelessComponent("CategoryOrHomeTitle");

let make = (~categories, ~generalSettings, _) => {
  ...component,
  render: _self =>
    <>
      {categories
       ->Option.flatMap(p => p##nodes)
       ->Option.flatMap(nodes => nodes[0])
       ->Option.flatMap(node => node)
       ->Option.flatMap(node =>
           node##description->Option.isSome ?
             node##description : node##name->Option.isSome ? node##name : None
         )
       ->Option.map(title =>
           <BsReactHelmet titleTemplate=Consts.titleTemplate>
             <title> title->ReasonReact.string </title>
           </BsReactHelmet>
         )
       ->Option.getWithDefault(
           generalSettings
           ->Option.flatMap(node => node##description)
           ->Option.map(title =>
               <BsReactHelmet titleTemplate=Consts.titleTemplateHome>
                 <title> title->ReasonReact.string </title>
               </BsReactHelmet>
             )
           ->Option.getWithDefault(ReasonReact.null),
         )}
    </>,
};
