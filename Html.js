// @flow
/* eslint-disable react/prop-types */

import React from "react";
import { Helmet } from "react-helmet";
import { AppRegistry } from "react-native-web";

const Html = ({ App, render } /*: PhenomicHtmlPropsType*/) => {
  AppRegistry.registerComponent("App", () => App);
  const app = AppRegistry.getApplication("App");
  const { Main, State, Script, Style } = render(app.element);
  const head = Helmet.renderStatic();
  return (
    <html {...head.htmlAttributes.toComponent()}>
      <head>
        {head.meta.toComponent()}
        {head.title.toComponent()}
        {head.base.toComponent()}
        {app.getStyleElement()}
        <Style />
        {head.link.toComponent()}
        {head.style.toComponent()}
        {head.script.toComponent()}
        {head.noscript.toComponent()}
      </head>
      <body {...head.bodyAttributes.toComponent()}>
        <Main />
        <State />
        <script src="https://polyfill.io/v3/polyfill.min.js?features=Map%2CSet%2CIntersectionObserver%2CIntersectionObserverEntry%2CResizeObserver" />
        <Script />
        {process.env.NODE_ENV === "production" && (
          <script
            dangerouslySetInnerHTML={{
              __html: `var _paq = window._paq || [];
_paq.push(['trackPageView']);
_paq.push(['enableLinkTracking']);
(function() {
  var u="//a.moox.fr/";
  _paq.push(['setTrackerUrl', u+'m']);
  _paq.push(['setSiteId', 2]);
  var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0];
  g.type='text/javascript'; g.async=true; g.defer=true; g.src=u+'m.js'; s.parentNode.insertBefore(g,s);
})();`,
            }}
          />
        )}
        {process.env.NODE_ENV === "production" && (
          <>
            <script
              async={true}
              src="https://www.googletagmanager.com/gtag/js?id=UA-158797869-1"
            />
            <script
              dangerouslySetInnerHTML={{
                __html: `window.dataLayer = window.dataLayer || [];
function gtag(){dataLayer.push(arguments);}
gtag('js', new Date());
gtag('config', 'UA-158797869-1');`,
              }}
            />
          </>
        )}
      </body>
    </html>
  );
};

export default Html;
