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
          width
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
    title
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

module Placeholders = {
  let postPreview: int => Fragments.PostPreviewFragment.t =
    i => {
      "id": "placeholder" ++ i->string_of_int,
      "title": None,
      "slug": None,
      "dateGmt": None,
      "commentCount": None,
      "likeCount": None,
      "featuredImage": None,
      "categories": None,
      "tags": None,
    };

  let postDetail: int => Fragments.PostDetailFragment.t =
    i => {
      "id": "placeholder" ++ i->string_of_int,
      "title": None,
      "slug": None,
      "commentCount": None,
      "likeCount": None,
      "postId": i,
      "dateGmt": None,
      "content": None,
      "comments": None,
      "categories": None,
      "tags": None,
    };
};
