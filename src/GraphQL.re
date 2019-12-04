module Fragments = [%graphql
  {|
  fragment CommentFragment on Comment {
    commentId
    parent {
      commentId
    }
    dateGmt
    content
    author {
      ... on User {
        userId
        name
        url
        email
      }
      ... on CommentAuthor {
        name
        url
        email
      }
    }
  }

  fragment PostPreviewFragment on Post {
    id
    title
    slug
    dateGmt
    commentCount
    likeCount
    featuredImage {
      mediaDetails {
        sizes {
          name
          sourceUrl
        }
      }
    }
    categories {
      nodes {
        name
        slug
        parent {
          id
        }
      }
    }
    tags {
      nodes {
        name
        slug
      }
    }
  }

  fragment PostDetailFragment on Post {
    id
    title(format: RAW)
    slug
    commentCount
    likeCount
    postId
    dateGmt
    content
    comments(
      first: 1000,
      where: {
        parent: 99999,
        orderby: COMMENT_DATE_GMT,
        order: ASC
      }
    ) {
      # 99999 is a trick defined in `graphql_comment_connection_query_args` (functions.php) filter to have all comments
      nodes {
        ...CommentFragment
      }
    }
    categories {
      nodes {
        name
        slug
        parent {
          id
        }
        posts(first: 5) {
          nodes {
            ...PostPreviewFragment
          }
        }
      }
    }
    tags(first: 100) {
      nodes {
        name
        slug
      }
    }
  }
|}
];
