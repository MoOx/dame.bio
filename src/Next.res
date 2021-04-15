@deriving(abstract)
type options = {
  @optional
  ssr: bool,
  @optional
  loading: unit => React.element,
}

@module("next/dynamic")
external dynamic: (unit => Js.Promise.t<'a>, options) => 'a = "default"

@val external \"import": string => Js.Promise.t<'a> = "import"

module Error = {
  @module("next/error") @react.component
  external make: (~statusCode: int, ~children: React.element) => React.element = "default"
}

module Head = {
  @module("next/head") @react.component
  external make: (~children: React.element) => React.element = "default"
}

// https://nextjs.org/docs/api-reference/next/image
module Image = {
  type loaderOptions = {
    src: string,
    width: float,
    quality: float,
  }
  @module("next/image") @react.component
  external make: (
    ~alt: string=?,
    ~className: string=?,
    ~height: float=?,
    ~layout: [#fixed | #intrinsic | #responsive | #fill]=?,
    ~loader: loaderOptions => string=?,
    ~loading: [
      | #"lazy"
      | #eager
    ]=?,
    ~priority: bool=?,
    ~objectFit: [
      | #fill
      | #contain
      | #cover
      | #none
      | #"scale-down"
    ]=?,
    ~objectPosition: string=?,
    ~quality: float=?,
    ~sizes: string=?,
    ~src: string,
    ~unoptimized: bool=?,
    ~width: float=?,
  ) => React.element = "default"
}

module Link = {
  @module("next/link") @react.component
  external make: (
    ~_as: string=?,
    ~children: React.element,
    ~className: option<string>=?,
    ~href: string,
    ~passHref: option<bool>=?,
    ~prefetch: bool=?,
    ~replace: option<bool>=?,
    ~shallow: option<bool>=?,
  ) => React.element = "default"
}

module Events = {
  type t

  @send
  external on: (
    t,
    @string
    [
      | #routeChangeStart(string => unit)
      | #routeChangeComplete(string => unit)
      | #hashChangeComplete(string => unit)
    ],
  ) => unit = "on"

  @send
  external off: (
    t,
    @string
    [
      | #routeChangeStart(string => unit)
      | #routeChangeComplete(string => unit)
      | #hashChangeComplete(string => unit)
    ],
  ) => unit = "off"
}

type router = {
  route: string,
  asPath: string,
  events: Events.t,
  pathname: string,
  query: Js.Dict.t<string>,
}

type pathObj = {
  pathname: string,
  query: Js.Dict.t<string>,
}
@module("next/router") external useRouter: unit => router = "useRouter"

module Router = {
  @send external push: (router, string) => unit = "push"
  @send external pushObj: (router, pathObj) => unit = "push"

  @send external replace: (router, string) => unit = "replace"
  @send external replaceObj: (router, pathObj) => unit = "replace"
}

module GetServerSideProps = {
  module Req = {
    type t
  }

  module Res = {
    type t

    @send external setHeader: (t, string, string) => unit = "setHeader"
    @send external write: (t, string) => unit = "write"
    @send external end_: t => unit = "end"
  }

  // See: https://github.com/zeit/next.js/blob/canary/packages/next/types/index.d.ts
  type context<'props, 'params> = {
    params: Js.t<'params>,
    query: Js.Dict.t<string>,
    req: Req.t,
    res: Res.t,
  }

  type t<'props, 'params> = context<'props, 'params> => Js.Promise.t<{"props": 'props}>
}

module GetStaticProps = {
  // See: https://github.com/zeit/next.js/blob/canary/packages/next/types/index.d.ts
  type context<'props, 'params> = {
    params: 'params,
    query: Js.Dict.t<string>,
    req: Js.Nullable.t<Js.t<'props>>,
  }

  type t<'props, 'params> = context<'props, 'params> => Js.Promise.t<{"props": 'props}>

  type revalidate<'props, 'params> = context<'props, 'params> => Js.Promise.t<{
    "props": 'props,
    "revalidate": int,
  }>
}

module GetStaticPaths = {
  // 'params: dynamic route params used in dynamic routing paths
  // Example: pages/[id].js would result in a 'params = { id: string }
  type path<'params> = {params: 'params}

  type return<'params> = {
    paths: array<path<'params>>,
    fallback: bool,
  }

  type t<'params> = unit => Js.Promise.t<return<'params>>
}
