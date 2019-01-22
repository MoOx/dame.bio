let damebio = {j|D'Âme Bio|j};
let title = {j|D'Âme Bio|j};
let defaultTitle =
  damebio ++ {j|: Recettes de cuisine saine, Permaculture, Bien-être|j};
let titleTemplate = {j|%s - |j} ++ damebio;
title ++ {j|: Recettes de cuisine saine, Permaculture, Bien-être|j};
let titleTemplate = {j|%s - |j} ++ title;

type menuLink = {
  link: string,
  text: string,
  icon:
    (~width: float, ~height: float, ~fill: string, unit) =>
    ReasonReact.reactElement,
  isActive: (string, string) => bool,
};

let menuLinks = [|
  {
    link: "/",
    text: {j|Home|j},
    icon: (~width, ~height, ~fill, _) => <SVGMenuHome width height fill />,
    isActive: (current, link) => current == link,
  },
  {
    link: "/alimentation/",
    text: {j|Alimentation|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuAlimentation width height fill />,
    isActive: (current, _link) =>
      Js.String.startsWith("/alimentation/", current),
  },
  {
    link: "/permaculture/",
    text: {j|Permaculture|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuPermaculture width height fill />,
    isActive: (current, _link) =>
      Js.String.startsWith("/permaculture/", current),
  },
  {
    link: "/bien-etre/",
    text: {j|Bien-Être|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuBienEtre width height fill />,
    isActive: (current, _link) =>
      Js.String.startsWith("/bien-etre/", current),
  },
  {
    link: "/lifestyle/",
    text: {j|Lifestyle|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuLifestyle width height fill />,
    isActive: (current, _link) =>
      Js.String.startsWith("/lifestyle/", current),
  },
|];
module Colors = {
  let darkest = "hsl(219.1, 100%, 2%)";
  let dark = "hsl(219.1, 100%, 8.5%)";
  let light = "hsl(219.1, 100%, 99%)";
  let lightest = "hsl(219.1, 100%, 99.5%)";
  let tabBarIconInactive = "#909192";
  let tabBarIconActive = "#FD2E55";
};
