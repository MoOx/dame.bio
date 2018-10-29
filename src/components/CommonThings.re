open Helpers;

let component = ReasonReact.statelessComponent("CommonThings");

let make = _ => {
  ...component,
  render: _self =>
    <Head>
      <meta charSet="utf-8" />
      <style>
        {
          {j|
html {
  height: 100%;
  /* background: black; */
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Ubuntu, "Helvetica Neue", sans-serif;
}
body {
  min-height:100%;
  background: url("/images/bg-paper-tile.jpg") repeat;
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
  font-family: IndieFlower;
  src: url(/fonts/IndieFlower-webfont.woff) format('woff');
  font-weight: normal;
  font-style: normal;
}

.dbPost {
  font-size: 14px;
  line-height: 1.8571428;
  color: #49443A;
}

.dbPost a {
  color: #3ba013;
}

.dbPost strong {
  font-weight: 800;
}

.dbPost img {
  margin: 20px 0;
  max-width: 100%;
}

.dbPost .ingredients dt,
.dbPost .tips-title {
  font-weight: 800;
  font-size: 16px;
}
|j}
          |> text
        }
      </style>
    </Head>,
};
