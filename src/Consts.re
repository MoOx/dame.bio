let backendUrl = "https://dame.bio/";
let backendGrapqlUrl = backendUrl ++ "graphql";
let backendWpAjaxUrl = backendUrl ++ "wp-admin/admin-ajax.php";
let title = {j|D'Âme Bio|j};
let titleTemplateHome = title ++ {j| - %s|j};
let titleTemplate = {j|%s - |j} ++ title;
let nickname = {j|Aurélie|j};
let shortBio = {j|Semeuse de graines et cultivatrice d’un mode de vie doux, naturel et respectueux de la Terre.|j};
let bio = {j|Auteure, professeure de hatha yoga, créatrice de contenus et permacultrice. Je partage mon cheminement personnel, mes expériences, conseils, réflexions, coups de coeur et connaissances avec bienveillance et amour. A travers ce blog, je souhaite éveiller, transmettre, partager, renouer avec notre nature, revenir à l’essentiel, impulser des changements positifs et des prises de conscience.|j};

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
  let darkLabel = "#49443A";
  let light = "hsl(219.1, 100%, 99%)";
  let lightest = "hsl(219.1, 100%, 99.5%)";
  let lightGrey = "#ebebeb";
  let darkGrey = "#666";
  let grey = "#909192";
  let tabBarIconInactive = "#909192";
  let tabBarIconActive = "#FD2E55";
  let main = "rgb(0, 101, 121)";
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
