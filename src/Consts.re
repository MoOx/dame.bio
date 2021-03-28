let frontendUrl = "https://dame.bio";
let backendUrl = "https://data.dame.bio";
let backendGrapqlUrl = backendUrl ++ "/graphql";
let title = {j|D'Âme Bio|j};
let titleTemplateHome = title ++ {j| - %s|j};
let titleTemplate = {j|%s - |j} ++ title;
let nickname = {j|Aurélie|j};
let shortBio = {j|Semeuse de graines et cultivatrice d’un mode de vie en lien avec la Nature pour prendre soin de soi, des autres et de la Terre.
Je partage avec vous mes explorations sur l’écologie, la nature, le bien-être et mon cheminement personnel.
Avec amour et bienveillance. Aurélie ♥︎|j};
let bio = {j|Auteure, enseignante de yoga, créatrice de contenus et coach en jardinage naturel. Je partage avec vous mes passions, expériences, conseils, réflexions, coups de coeur et des alternatives saines, durables et respectueuses de l’environnement que je mets en place dans mon quotidien tout en vivant pleinement.
À travers cet espace, je souhaite éveiller, transmettre, partager, se reconnecter à la nature, revenir à l’essentiel, impulser des prises de conscience et des changements positifs. |j};

module Menus = {
  let main = "TWVudTo5ODU="; // Menu:985
  let categories = "TWVudTo5ODQ="; // Menu:984
  let more = "TWVudTo5ODY="; // Menu:986
};

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
      <SVGSocialInstagram
        fill=iconColor
        width={iconSize->Js.Float.toString}
        height={iconSize->Js.Float.toString}
      />,
  },
  {
    title: "Facebook",
    text: "@Damebio sur Facebook",
    link: "https://www.facebook.com/Damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialFacebook
        fill=iconColor
        width={iconSize->Js.Float.toString}
        height={iconSize->Js.Float.toString}
      />,
  },
  {
    title: "Pinterest",
    text: "@Damebio sur Pinterest",
    link: "https://www.pinterest.com/damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialPinterest
        fill=iconColor
        width={iconSize->Js.Float.toString}
        height={iconSize->Js.Float.toString}
      />,
  },
  {
    title: "Twitter",
    text: "@Damebio sur Twitter",
    link: "https://twitter.com/damebio/",
    componentFunc: (~iconColor, ~iconSize) =>
      <SVGSocialTwitter
        fill=iconColor
        width={iconSize->Js.Float.toString}
        height={iconSize->Js.Float.toString}
      />,
  },
|];

module Colors = {
  let darkest = "hsl(219.1, 100%, 2%)";
  let dark = "hsl(219.1, 100%, 8.5%)";
  let darkLabel = "#49443A";
  let light = "hsl(219.1, 100%, 99%)";
  let lightest = "hsl(219.1, 100%, 99.5%)";
  let lightGrey = "#ebebeb";
  let darkGrey = "#666";
  let grey = "#909192";
  let tabBarIconInactive = "#909192";
  let tabBarIconActive = "#FD2E55";
  let main = "#006579";
  let main50 = "rgba(0, 101, 121, 0.5)";
  let alt = "#67B44B";
  let pink = "#DE6D88";
  let error = "red";
  let success = main;
};

module Radius = {
  let field = 20.;
  let box = 10.;
  let avatar = 100.;
  let avatarBig = 500.;
};
