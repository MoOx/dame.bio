%graphql(`
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
    databaseId
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
      # 99999 is a trick defined in graphql_comment_connection_query_args (functions.php) filter to have all comments
      nodes {
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
  `)

module GetGlobals = %graphql(`
  query getGlobal {
    generalSettings {
      title
      description
    }
    menus {
      nodes {
        id
        slug
        menuItems {
          nodes {
            label
            url
          }
        }
      }
    }
  }
  `)

let useGlobals = () =>
  switch GetGlobals.use() {
  | {loading: true} => None
  | {data: Some(response)} => Some(response)
  | {error: Some(error)} =>
    Js.Console.error(("GetGlobals", error))
    None
  | _ => None
  }

module GetPagesAndPosts = %graphql(`
  query GetPagesAndPosts($first: Int, $last: Int, $pageSlug: String, $categorySlug: String, $tagSlug: String, $cursorAfter: String, $cursorBefore: String){
    categories(first: 1, where: {slug: [$categorySlug]}) {
      nodes {
        id
        name
        description
      }
    }
    posts(first: $first, last: $last, after: $cursorAfter, before: $cursorBefore, where: {categoryName: $categorySlug, tag: $tagSlug}) {
      pageInfo {
        startCursor
        endCursor
        hasNextPage
        hasPreviousPage
      }
      nodes {
        ...PostPreviewFragment
      }
    }
    pages(first: 1, where: {name: $pageSlug}) {
      nodes {
        id
        title
        slug
        dateGmt
        content
      }
    }
  }
  `)

module GetPost = %graphql(`
  query GetPost($postSlug: ID!){
    post(id: $postSlug, idType: SLUG) {
      ...PostDetailFragment
    }
  }`)

module GetPostById = %graphql(`
  query GetPost($postId: ID!){
    post(id: $postId, idType: DATABASE_ID) {
      ...PostDetailFragment
    }
  }`)

module GetPreviewPost = %graphql(`
  query GetPreviewPost($id: ID!) {
    post(id: $id, idType: DATABASE_ID) {
      databaseId
      status
    }
  }`)

module GetPage = %graphql(`
  query GetPage($pageSlug: ID!){
    page(id: $pageSlug, idType: SLUG) {
      id
      title
      slug
      dateGmt
      content
    }
  }
  `)

module Placeholders = {
  let postPreview: int => PostPreviewFragment.t = i => {
    __typename: "PostPreviewFragment",
    id: "placeholder" ++ i->string_of_int,
    title: None,
    slug: None,
    dateGmt: None,
    commentCount: None,
    likeCount: None,
    featuredImage: None,
    categories: None,
    tags: None,
  }
  // let postDetail: int => PostDetailFragment.t = i => {
  //   __typename: "PostDetailFragment",
  //   id: "placeholder" ++ i->string_of_int,
  //   title: None,
  //   slug: None,
  //   commentCount: None,
  //   likeCount: None,
  //   databaseId: i,
  //   dateGmt: None,
  //   content: None,
  //   comments: None,
  //   categories: None,
  //   tags: None,
  // }
}
