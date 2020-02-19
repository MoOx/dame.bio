/* eslint-disable import/max-dependencies */

import React from "react";
import { Router, Route, browserHistory } from "react-router";
import { AppRegistry, Dimensions } from "react-native-web";
import { createApp, renderApp } from "@phenomic/preset-react-app/lib/client";
// eslint-disable-next-line import/no-extraneous-dependencies
import gql from "graphql-tag";

import initApollo from "./src/init-apollo.js";
import RoutePostsOrPage from "./src/components/RoutePostsOrPage.bs.js";
import RoutePostBySlug from "./src/components/RoutePostBySlug.bs.js";
import RoutePostById from "./src/components/RoutePostById.bs.js";
import RouteContact from "./src/components/RouteContact.bs.js";
import RouteError from "./src/components/RouteError.bs.js";

// SSR pre-defined window/screen dimensions
// choice for values has been made according to site stats
if (typeof window === "undefined") {
  Dimensions.set({
    window: {
      width: 360,
      height: 640,
    },
    screen: {
      width: 360,
      height: 640,
    },
  });

  const apolloClient = initApollo();
  const first = 1000;

  RouteError.getAllPossibleUrls = async () => {
    return ["/404.html"];
  };

  RoutePostsOrPage.getAllPossibleUrls = async ({ path }) => {
    if (path == "/") {
      return ["/"];
    }

    // /:categoryOrPageSlug/ (categories)
    // /:categoryOrPageSlug/after/:cursorAfter
    // /:tag
    // /:tag/after/:cursorAfter (disabled, see comment below)
    if (path === "/:categoryOrPageSlug/after/:cursorAfter/") {
      return apolloClient
        .query({
          query: gql`
            {
              posts(first: ${first}, where: { status: PUBLISH }) {
                edges {
                  cursor
                  node {
                    categories {
                      nodes {
                        slug
                      }
                    }
                    tags {
                      nodes {
                        slug
                      }
                    }
                  }
                }
              }
            }
          `,
        })
        .then(({ data }) => {
          // console.log(`received data ${JSON.stringify(data, null, 2)}`);
          return data.posts.edges.reduce((acc, item) => {
            try {
              acc.push("/after/" + item.cursor + "/");
              if (
                item.node &&
                item.node.categories &&
                item.node.categories.nodes
              ) {
                item.node.categories.nodes.forEach(c => {
                  acc.push("/" + c.slug + "/");
                  acc.push("/" + c.slug + "/after/" + item.cursor + "/");
                });
              }
              if (item.node && item.node.tags && item.node.tags.nodes) {
                item.node.tags.nodes.forEach(t => {
                  acc.push("/tag/" + t.slug + "/");
                  // disable SSR for tag pagination because this adds lots of urls to pre-render
                  // and until we have better perfs (= local db/fetch) it's totally slow to do this...
                  // acc.push("/tag/" + t.slug + "/after/" + item.cursor + "/");
                });
              }
            } catch (e) {
              console.log(`received error ${e}`);
              console.log(JSON.stringify(item, null, 2));
            }
            return acc;
          }, []);
        })
        .catch(error => {
          console.log(`received error ${error}`);
          return [];
        });
    }

    // /:categoryOrPageSlug/ (pages)
    if (path === "/:categoryOrPageSlug/") {
      return apolloClient
        .query({
          query: gql`
          {
            pages(first: ${first}, where: { status: PUBLISH }) {
              edges {
                node {
                  slug
                }
              }
            }
          }
        `,
        })
        .then(({ data }) => {
          return data.pages.edges
            .map(item => {
              try {
                return "/" + item.node.slug + "/";
              } catch (e) {
                console.log(`received error ${e}`);
                console.log(JSON.stringify(item, null, 2));
              }
            })
            .filter(i => i);
        })
        .catch(error => {
          console.log(`received error ${error}`);
          return [];
        });
    }

    return [];
  };

  // already available via page slug
  RouteContact.getAllPossibleUrls = () => {
    return [];
  };

  // /:categoryOrPageSlug/:postSlug/
  RoutePostBySlug.getAllPossibleUrls = async () => {
    return apolloClient
      .query({
        query: gql`
          {
            posts(first: ${first}, where: { status: PUBLISH }) {
              edges {
                node {
                  slug
                  categories(first: 1) {
                    nodes {
                      slug
                    }
                  }
                }
              }
            }
          }
        `,
      })
      .then(({ data }) => {
        return data.posts.edges
          .map(item => {
            try {
              return (
                "/" +
                item.node.categories.nodes[0].slug +
                "/" +
                item.node.slug +
                "/"
              );
            } catch (e) {
              console.log(`received error ${e}`);
              console.log(JSON.stringify(item, null, 2));
            }
          })
          .filter(i => i);
      })
      .catch(error => {
        console.log(`received error ${error}`);
        return [];
      });
  };
}

let onUpdate = () => console.info("onUpdate", window.location.href);
if (
  process.env.NODE_ENV === "production" &&
  typeof window != undefined &&
  typeof window._paq != undefined
) {
  onUpdate = () => {
    window._paq.push(["setCustomUrl", window.location.href]);
    window._paq.push(["setDocumentTitle", document.title]);
    window._paq.push(["trackPageView"]);
  };
}

const routes = () => (
  <Router history={browserHistory} onUpdate={onUpdate}>
    <Route path="/" component={RoutePostsOrPage} />
    <Route path="/after/:cursorAfter/" component={RoutePostsOrPage} />
    <Route path="/contact/" component={RouteContact} />
    <Route path="/tag/:tagSlug/" component={RoutePostsOrPage} />
    <Route
      path="/tag/:tagSlug/after/:cursorAfter/"
      component={RoutePostsOrPage}
    />
    <Route path="/:categoryOrPageSlug/" component={RoutePostsOrPage} />
    <Route
      path="/:categoryOrPageSlug/after/:cursorAfter/"
      component={RoutePostsOrPage}
    />
    <Route path="/:categoryOrPageSlug/:postSlug/" component={RoutePostBySlug} />
    {/* backward compat */}
    <Route path="/:categoryOrPageSlug/:postSlug" component={RoutePostBySlug} />
    <Route
      path="/:categoryOrPageSlug/:postSlug/feed"
      component={RoutePostBySlug}
    />
    <Route path="/noindex/post/:postId/" component={RoutePostById} />
    <Route path="/*" component={RouteError} />
  </Router>
);

const render = (rootComponent, rootTag) => {
  AppRegistry.registerComponent("App", () => () => rootComponent);
  AppRegistry.runApplication("App", { rootTag });
};

export default createApp(routes, render);

if (module.hot) {
  module.hot.accept(() => renderApp(routes, render));
}

// it's that easy to have for initial loading ?
// will have to double check in prod (static)
if (typeof window !== "undefined") {
  window.addEventListener("load", () => {
    // eslint-disable-next-line import/no-extraneous-dependencies
    require("@phenomic/plugin-renderer-react/lib/components/Link.hash.js").default(
      window.location.hash,
    );
  });
}
