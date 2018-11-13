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
  background: #fefefe;
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

.dbPost {
  font-size: 16px;
  line-height: 29px;
  color: #49443A;
}

  .dbPost a {
    color: #3ba013;
  }

  .dbPost strong {
    font-weight: 800;
  }

  .dbPost img {
    /* margin: 20px 0; */
    max-width: 100%;
  }

  .dbPost .ingredients dt,
  .dbPost .tips-title {
    font-weight: 800;
    font-size: 18px;
  }

  .dbPost dd {
    margin: 0 0 0 20px;
  }
  
  .dbPost dd::before {
    content: "· "
  }
  
.wp-block-image {
  margin: 40px;
}

  .wp-block-image .dbtmp-element-protector-wrapper {
    display: block;
    position: relative;
  }

  .wp-block-image .dbtmp-element-protector-wrapper img {
    display: block;
  }

  .wp-block-image .dbtmp-element-protector-overlay {
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
  }
  
  .wp-block-image figcaption {
    color: #555d66;
    font-size: 14px;
    margin-bottom: 1em;
    margin-top: .5em;
    text-align: center;
  }

/* keep wordpress html default rendering */
.dbComment { white-space: normal }
.dbComment p { margin: 0; }
|j}
          |> text
        }
      </style>
    </Head>,
};
