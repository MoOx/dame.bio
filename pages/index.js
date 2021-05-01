// export { getStaticPaths } from "../src/pages/PagePostsOrPage.bs.js";
// export { getStaticProps } from "../src/pages/PagePostsOrPage.bs.js";
import page from "../src/pages/PagePostsOrPage.bs.js";
export default page;

import { perPageForHome } from "../src/pages/PagePostsOrPage.bs.js";
import { GetGlobals, GetPageAndPostsFromSlug } from "../src/WPGraphQL.bs.js";
import { initializeApollo, injectApolloState } from "../src/apolloClient.js";

export async function getStaticProps() {
  const apolloClient = initializeApollo();
  await apolloClient.query({
    query: GetGlobals.query,
    variables: {},
  });
  await apolloClient.query({
    query: GetPageAndPostsFromSlug.query,
    variables: {
      pageSlug: "noop",
      categorySlug: "",
      first: perPageForHome,
    },
  });

  return injectApolloState(apolloClient, {
    // revalidate: 30,
  });
}
