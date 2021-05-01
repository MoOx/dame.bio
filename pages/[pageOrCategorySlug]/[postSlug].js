// export { getStaticPaths } from "../../src/pages/PagePostBySlug.bs.js";
// export { getStaticProps } from "../../src/pages/PagePostBySlug.bs.js";
import page from "../../src/pages/PagePostBySlug.bs.js";
export default page;

import { gql } from "@apollo/client";
import { GetGlobals, GetPost } from "../../src/WPGraphQL.bs.js";
import { initializeApollo, injectApolloState } from "../../src/apolloClient.js";

export async function getStaticProps(ctx) {
  const apolloClient = initializeApollo();
  await apolloClient.query({
    query: GetGlobals.query,
    variables: {},
  });
  await apolloClient.query({
    query: GetPost.query,
    variables: {
      postSlug: ctx.params.postSlug,
    },
  });

  return injectApolloState(apolloClient, {
    // revalidate: 30,
    props: {
      postSlug: ctx.params.postSlug,
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
            nodes {
              slug
              categories(first: 1) {
                nodes {
                  slug
                }
              }
            }
          }
        }
      `,
    })
    .then(({ data }) => {
      return data.posts.nodes
        .map((item) => "/" + item.categories.nodes[0].slug + "/" + item.slug)
        .filter((i) => i);
    })
    .catch((error) => {
      console.log(`received error ${error}`);
      return [];
    });
  return {
    paths,
    fallback: false,
  };
}
