import { backendGrapqlUrl } from "../../src/Consts.bs.js";
import { GetPreviewPost } from "../../src/WPGraphQL.bs.js";
import { initializeApollo, injectApolloState } from "../../src/apolloClient.js";

export default async function preview(req, res) {
  const { secret, id, authToken } = req.query;

  if (
    !process.env.WORDPRESS_PREVIEW_SECRET ||
    secret !== process.env.WORDPRESS_PREVIEW_SECRET
  ) {
    return res.status(401).json({ message: "Invalid secret" });
  }

  if (!id) {
    return res.status(401).json({ message: "No id" });
  }

  const apolloClient = initializeApollo(null, authToken);
  const result = await apolloClient.query({
    query: GetPreviewPost.query,
    variables: {
      id: parseInt(id, 10),
    },
  });
  if (result.errors) {
    console.error(result.errors);
    throw new Error("Failed to fetch API");
  }
  console.log(result);
  if (!result.data.post) {
    return res.status(401).json({ message: "Post not found" });
  }

  res.setPreviewData({
    post: {
      databaseId: result.data.post.databaseId,
      status: result.data.post.status,
    },
    authToken,
  });

  // Don't redirect to `req.query.slug` as that might lead to open redirect vulnerabilities
  res.writeHead(307, {
    Location: `/preview/post-by-id/${result.data.post.databaseId}`,
  });
  res.end();
}
