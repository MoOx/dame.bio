// export { getStaticPaths } from "../../../src/pages/PagePostById.bs.js";
// export { getStaticProps } from "../../../src/pages/PagePostById.bs.js";
import page from "../../../src/pages/PagePostById.bs.js";
export default page;

import { gql } from "@apollo/client";
import { GetGlobals, GetPostById } from "../../../src/WPGraphQL.bs.js";
import {
  initializeApollo,
  injectApolloState,
} from "../../../src/apolloClient.js";

export async function getServerSideProps(ctx) {
  const apolloClient = initializeApollo(null, ctx.previewData.authToken);
  await apolloClient.query({
    query: GetGlobals.query,
    variables: {},
  });
  await apolloClient.query({
    query: GetPostById.query,
    variables: {
      postId: ctx.params.postId,
    },
  });

  return injectApolloState(apolloClient, {
    // revalidate: 30,
    props: {
      postId: ctx.params.postId,
      authToken: ctx.previewData.authToken,
    },
  });
}
