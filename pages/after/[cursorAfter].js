// export { getStaticPaths } from "../../src/pages/PagePostsOrPage.bs.js";
// export { getStaticProps } from "../../src/pages/PagePostsOrPage.bs.js";
import page from "../../src/pages/PagePostsOrPage.bs.js";
export default page;

import { gql } from "@apollo/client";
import { perPage } from "../../src/pages/PagePostsOrPage.bs.js";
import { GetGlobals, GetPagesAndPosts } from "../../src/WPGraphQL.bs.js";
import { initializeApollo, injectApolloState } from "../../src/apolloClient.js";

export async function getStaticProps(ctx) {
  const apolloClient = initializeApollo();
  await apolloClient.query({
    query: GetGlobals.query,
    variables: {},
  });
  await apolloClient.query({
    query: GetPagesAndPosts.query,
    variables: {
      pageSlug: "noop",
      categorySlug: "",
      first: perPage,
      cursorAfter: ctx.params.cursorAfter,
    },
  });

  return injectApolloState(apolloClient, {
    revalidate: false,
    props: {
      cursorAfter: ctx.params.cursorAfter,
    },
  });
}

export async function getStaticPaths(ctx) {
  const apolloClient = initializeApollo();
  const paths = await apolloClient
    .query({
      query: gql`
        {
          posts(first: 1000, where: { status: PUBLISH }) {
            edges {
              cursor
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
            return "/after/" + item.cursor;
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
  return {
    paths,
    fallback: false,
  };
}
