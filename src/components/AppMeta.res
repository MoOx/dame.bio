open Consts.Colors
let radius = Consts.Radius.box->Js.Float.toFixed ++ "px"

@react.component
let make = () => {
  <Next.Head>
    <meta charSet="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover" />
    <style
      dangerouslySetInnerHTML={
        "__html": `@-ms-viewport { width: device-width } @viewport { width: device-width }`,
      }
    />
    <link rel="preconnect" href="https://data.dame.bio" />
    <meta name="description" content=Consts.shortBio />
    <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png" />
    <link rel="icon" type_="image/png" sizes="32x32" href="/favicon-32x32.png" />
    <link rel="icon" type_="image/png" sizes="16x16" href="/favicon-16x16.png" />
    <link rel="manifest" href="/site.webmanifest" />
    {
      // <link rel="mask-icon" href="/safari-pinned-tab.svg" color="#006579" />
      ReactDOMRe.createDOMElementVariadic(
        "link",
        ~props={
          "rel": "mask-icon",
          "href": "/safari-pinned-tab.svg",
          "color": "#006579",
        }->Obj.magic,
        [],
      )
    }
    <meta name="msapplication-TileColor" content="#006579" />
    <meta name="theme-color" content="#ffffff" />
    <style
      dangerouslySetInnerHTML={
        "__html": j`
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

.menu-backdrop {
  background-color: rgba(253, 255, 255, .98);
}
@supports ((-webkit-backdrop-filter: blur(14px)) or (backdrop-filter: blur(14px))) {
  .menu-backdrop {
    background-color: rgba(245, 245, 245, .75);
    -webkit-backdrop-filter: saturate(200%) brightness(150%) grayscale(20%) blur(20px);
    backdrop-filter: saturate(200%) brightness(150%) grayscale(20%) blur(20px);
  }
}

@media (min-width: 501px) {
  .device-small {
    display: none;
  }
}
@media (max-width: 500px) {
  .device-large {
    display: none;
  }
}

/* https://github.com/necolas/react-native-web/issues/1250 */
.ScrollView-snapToAlignment-center > div > div > div { scroll-snap-align: center !important }

/* until we migrate and remove contact form <form> from the page */
.DameBioHtml .wpcf7 {display: none !important}

/* wordpress post/page */
.DameBioHtml {
  font-size: 18px;
  line-height: calc(18px * 1.65);
  color: #333;
}
.DameBioHtml a {
  color: #3ba013;
}
.DameBioHtml strong {
  font-weight: 800;
}
.DameBioHtml img {
  max-width: 100%;
}

.DameBioHtml .ingredients dt,
.DameBioHtml h2 {
  margin: 40px 0 20px;
  font-size: 26px;
  line-height: calc(1.5 * 26px);
  font-weight: 600;
  color: #111;
}

.DameBioHtml .ingredients dt::before,
.DameBioHtml h2::before {
  content: "☆  ";
  font-weight: 100;
}

.DameBioHtml--permaculture h2::before { content: "🍃 " }

.DameBioHtml dd { margin: 0 }
.DameBioHtml .wp-block-image { margin: 0 }

.DameBioHtml .Db-Media {
  position: relative;
  display: block;
  margin: 40px auto;
  max-width: calc(100% - 40px * 2);
  background: $lightGrey;
  border-radius: 6px;
  overflow: hidden;
}

@media (max-width: 640px) {
  .DameBioHtml .Db-Media {
    margin: 20px -20px;
    max-width: calc(100% + 20px * 2);
  }
}

.DameBioHtml .Db-Media img {display: block;}
.DameBioHtml .Db-Media-overlay {position:absolute;top:0;left:0;right:0;bottom:0;}

.DameBioHtml figcaption {
  color: #555d66;
  font-size: 14px;
  margin-top: 10px;
  text-align: center;
}

/* keep wordpress html default rendering */
.DameBioHtml .dbComment { white-space: normal }
.DameBioHtml .dbComment p { margin: 0; }
.DameBioHtml .dbComment a { color: #49443A; }

.DameBioHtml blockquote {
  border-left: 4px solid #b9c840;
  margin: 0;
  padding: 0 1em;
}

.DameBioHtml .conseils {
  position: relative;
  margin: 2em 0;
  padding: 1em 1.5em;
  background: #fff;
  z-index: 1;
}

.DameBioHtml .conseils > :first-child {
  text-transform: uppercase;
  font-size: 13px;
  font-weight: 800;
}

.DameBioHtml .conseils::before {
  display: block;
  position: absolute;
  left: 0em;
  top: 0em;
  content: " ";
  width: 120px;
  height: 60px;
  border-top: 2px solid #b9c840;
  border-left: 2px solid #b9c840;
  border-top-left-radius: 6px;
}

.DameBioHtml .conseils::after {
  display: block;
  position: absolute;
  right: 0;
  bottom: 0;
  content: " ";
  width: 120px;
  height: 60px;
  border-bottom: 2px solid #b9c840;
  border-right: 2px solid #b9c840;
  border-bottom-right-radius: 6px;
}
`,
      }
    />
  </Next.Head>
}
