// export { getStaticPaths } from "../src/pages/PagePostsOrPage.bs.js";
// export { getStaticProps } from "../src/pages/PagePostsOrPage.bs.js";
import page from "../src/pages/PagePostsOrPage.bs.js";
export default page;

import { gql } from "@apollo/client";
import { perPage } from "../src/pages/PagePostsOrPage.bs.js";
import { GetGlobals, GetPageAndPostsFromSlug } from "../src/WPGraphQL.bs.js";
import { initializeApollo, injectApolloState } from "../src/apolloClient.js";

export async function getStaticProps(ctx) {
  const apolloClient = initializeApollo();
  await apolloClient.query({
    query: GetGlobals.query,
    variables: {},
  });
  await apolloClient.query({
    query: GetPageAndPostsFromSlug.query,
    variables: {
      first: perPage,
      pageSlug: ctx.params.pageOrCategorySlug,
      categorySlug: "",
    },
  });

  return injectApolloState(apolloClient, {
    // revalidate: 30,
    props: {
      pageOrCategorySlug: ctx.params.pageOrCategorySlug,
    },
  });
}

export async function getStaticPaths(ctx) {
  const apolloClient = initializeApollo();
  const paths = await apolloClient
    .query({
      query: gql`
        {
          pages(first: 1000, where: { status: PUBLISH }) {
            edges {
              node {
                slug
              }
            }
          }
          categories {
            nodes {
              slug
            }
          }
        }
      `,
    })
    .then(({ data }) => {
      return [
        ...data.pages.edges
          .map((item) => {
            try {
              return "/" + item.node.slug;
            } catch (e) {
              console.log(`received error ${e}`);
              console.log(JSON.stringify(item, null, 2));
            }
          })
          .filter((i) => i && i !== "/contact"),
        ...data.categories.nodes
          .map((item) => {
            try {
              return "/" + item.slug;
            } catch (e) {
              console.log(`received error ${e}`);
              console.log(JSON.stringify(item, null, 2));
            }
          })
          .filter((i) => i),
      ];
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
