open Belt;

let title = {j|D'Âme Bio|j};
let titleTemplateHome = title ++ {j| - %s|j};
let titleTemplate = {j|%s - |j} ++ title;
let nickname = {j|Aurélie|j};
let shortBio = {j|Semeuse de graines vertes et cultivatrice d’un mode de vie doux, naturel et respectueux de la planète.|j};
let bio = {j|Auteure, professeure de hatha yoga, créatrice de contenus et permacultrice. Je partage mon cheminement personnel, mes expériences, conseils, réflexions, coups de coeur et connaissances avec bienveillance et amour. A travers ce blog, je souhaite éveiller, transmettre, partager, renouer avec notre nature, revenir à l’essentiel, impulser des changements positifs et des prises de conscience.|j};

type tabBarLink = {
  link: string,
  text: string,
  icon: (~width: float, ~height: float, ~fill: string, unit) => React.element,
  isActive: (string, string) => bool,
};

type menuLink = {
  link: string,
  text: string,
  isActive: (string, string) => bool,
};

let categoriesLinks = [|
  {
    link: "/alimentation/",
    text: {j|Alimentation|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuAlimentation width height fill />,
    isActive: (current, _link) =>
      Js.String.startsWith("/alimentation/", current),
  },
  {
    link: "/yoga/",
    text: {j|Yoga|j},
    icon: (~width, ~height, ~fill, _) =>
      <SVGMenuLifestyle width height fill />,
    isActive: (current, _link) => Js.String.startsWith("/yoga/", current),
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

let menuLinks =
  categoriesLinks
  ->Array.map(l => {link: l.link, text: l.text, isActive: l.isActive})
  ->Array.concat([|
      {
        link: "/a-propos/",
        text: {j|À propos|j},
        isActive: (current, link) => current == link,
      },
    |]);

let tabBarLinks =
  [|
    {
      link: "/",
      text: {j|Accueil|j},
      icon: (~width, ~height, ~fill, _) => <SVGMenuHome width height fill />,
      isActive: (current, link) => current == link,
    },
  |]
  ->Array.concat(categoriesLinks);

type socialLink = {
  title: string,
  text: string,
  link: string,
  componentFunc: (~iconColor: string, ~iconSize: float) => React.element,
};

let socialLinks = [|
  {
    title: "Instagram",
    text: "@Damebio sur Instagram",
    link: "https://www.instagram.com/dame.bio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialInstagram fill=iconColor width=iconSize height=iconSize />,
  },
  {
    title: "Pinterest",
    text: "@Damebio sur Pinterest",
    link: "https://www.pinterest.com/damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialPinterest fill=iconColor width=iconSize height=iconSize />,
  },
  {
    title: "Twitter",
    text: "@Damebio sur Twitter",
    link: "https://twitter.com/damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialTwitter fill=iconColor width=iconSize height=iconSize />,
  },
  {
    title: "Facebook",
    text: "@Damebio sur Facebook",
    link: "https://www.facebook.com/Damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialFacebook fill=iconColor width=iconSize height=iconSize />,
  },
|];

module Colors = {
  let darkest = "hsl(219.1, 100%, 2%)";
  let dark = "hsl(219.1, 100%, 8.5%)";
  let light = "hsl(219.1, 100%, 99%)";
  let lightest = "hsl(219.1, 100%, 99.5%)";
  let lightGrey = "#ebebeb";
  let darkGrey = "#666";
  let grey = "#909192";
  let tabBarIconInactive = "#909192";
  let tabBarIconActive = "#FD2E55";
  let main = "#006579";
  let alt = "#67B44B";
};
