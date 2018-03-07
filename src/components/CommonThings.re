open Helpers;

let component = ReasonReact.statelessComponent("CommonThings");

let make = (_) => {
  ...component,
  render: _self =>
    <Head>
      <style>
        (
          {j|
html {
  height: 100%;
  background: black;
}
body {
  min-height:100%;
}

@supports(padding: max(0px)) {
  body {
    /* https://webkit.org/blog/7929/designing-websites-for-iphone-x/ */
    padding-left: env(safe-area-inset-left);
    padding-right: env(safe-area-inset-right);
    /* padding-left: max(12px, env(safe-area-inset-left)); */
    /* padding-right: max(12px, env(safe-area-inset-right)); */
    padding-bottom: env(safe-area-inset-bottom);
  }
}

@font-face {
  font-family: 'IndieFlower';
  src: url('public/assets/fonts/IndieFlower-webfont.woff') format('woff');
  font-weight: normal;
  font-style: normal;
}
|j}
          |> text
        )
      </style>
    </Head>
};
