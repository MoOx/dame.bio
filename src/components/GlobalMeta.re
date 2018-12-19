let component = ReasonReact.statelessComponent("GlobalMeta");

let make = _ => {
  ...component,
  render: _self => {
    <BsReactHelmet defaultTitle=Consts.defaultTitle>
      <meta charSet="utf-8" />
      <meta
        name="viewport"
        content="width=device-width, initial-scale=1, viewport-fit=cover"
      />
      <style>
        {j|@-ms-viewport { width: device-width } @viewport { width: device-width }|j}
        ->ReasonReact.string
      </style>
      <style>
        {j|
html {
  height: 100%;
  background: #006579;
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Ubuntu, "Helvetica Neue", sans-serif;
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
  font-family: IndieFlower;
  src: url(/fonts/IndieFlower-webfont.woff) format('woff');
  font-weight: normal;
  font-style: normal;
}

@media (min-width: 500px) {
  .device-small {
    display: none;
  }
}
@media (max-width: 501px) {
  .device-large {
    display: none;
  }
}
|j}
        ->ReasonReact.string
      </style>
    </BsReactHelmet>;
  },
};
