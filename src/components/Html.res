open Belt
open ReactNative

type mediaDataEntrySize = {
  "name": option<string>,
  "width": option<float>,
  "height": option<float>,
  "sourceUrl": option<string>,
}
type mediaDataEntry = {"title": option<string>, "sizes": option<array<mediaDataEntrySize>>}
type mediaData = Js.Dict.t<mediaDataEntry>
@scope("JSON") @val
external parseMediaData: string => mediaData = "parse"

let imageQuality = 75.
let imageFallbackWidth = 300.
let imageFallbackHeight = 300.
let imageMaxWidth = 500.

@react.component
let make = (~content, ~category: option<WPGraphQL.PostDetailFragment.t_categories_nodes>=?, ()) => {
  let cat = category->Option.flatMap(c => c.slug)->Category.from
  // @todo to migrate from wordpress filters
  // - callback_ingredients
  // - callback_blocks
  // - [slideshow] shortcodes that just add all images after first <p>
  let transformedContent =
    content
    ->Option.getWithDefault("")
    ->Utils.adjustUrls
    /* remove html comment to avoid mess */
    ->Js.String2.replaceByRe(%re("/<!--[\s\S]*?-->/g"), "")
    /* custom behavior decided for us hr => a png */
    ->Js.String2.replaceByRe(
      %re("/<hr ?(class=\"wp-block-separator\")? ?\\/?>/g"),
      Separator.makeAsString(cat),
    )
    /* custom behavior decided for us "white star unicode" => a png */
    ->Js.String2.replaceByRe(
      %re(
        "/<p (style=\"text-align:center\"|class=\"has-text-align-center\")>(☆|✩|⭐︎)<\\/p>/g"
      ),
      "" ++
      "<span style=\"display: block; text-align: center; margin: 40px;\">" ++
      "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />" ++ "</span>",
    )
    /* custom behavior decided for us --- => a png */
    ->Js.String2.replaceByRe(
      %re("/<p (style=\"text-align:center\"|class=\"has-text-align-center\")>---<\\/p>/g"),
      "" ++
      "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 40px auto; width: 80%;\">" ++
      "<img src=\"/images/separator-long-head.png\" style=\"width: 14.5px; height: 7.5px; margin: 1px 0 0 0;\" alt=\"\" />" ++
      "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>" ++
      "<img src=\"/images/separator-long-tail.png\" style=\"width: 64px; height: 19.5px;\" alt=\"\" />" ++ "</span>",
    )
  // transformedContent->Js.String2.splitByRe()
  let mediaDataRe = %re("/<span id=\"db-media-data\" style=\"display:none\">(.*)<\/span>/")
  let mediaDataResult = transformedContent->Js.String2.match_(mediaDataRe)
  let mediaDataRaw = mediaDataResult->Option.flatMap(result => result[1])
  let mediaData = mediaDataRaw->Option.map(parseMediaData)

  // good posts to test
  // http://localhost:3000/alimentation/les-meilleurs-endroits-pour-manger-bio-sain-sans-gluten-sans-lait-vegetarien-ou-vegan-a-londres
  // http://localhost:3000/alimentation/riz-au-lait-damande-miel-et-vanille-sans-lactose
  // http://localhost:3000/alimentation/gateau-a-l-amande-sans-gluten-sans-lait-sans-beurre-et-sans-farine
  // http://localhost:3000/bien-etre/meditation-du-lac-demeraude
  // http://localhost:3000/alimentation/menu-bio-pour-6-personnes-avec-la-vaisselle-jetable-biodegradable-de-dinovia
  let cleanHtmlTagStartRe = %re("/(<[a-z]+(\s[^>]*)?>)+$/")
  let cleanHtmlTagEndRe = %re("/^(<\/[a-z]+>)+/")
  let imageRe = %re(
    "/(<div(\s[^>]*)?><figure(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span>(<figcaption(\s[^>]*)?>[^>]*<\/figcaption>)?<\/figure><\/div>)|(<p(\s[^>]*)?><figure(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span>(<figcaption(\s[^>]*)?>[^>]*<\/figcaption>)?<\/figure><\/p>)|(<figure(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span>(<figcaption(\s[^>]*)?>[^>]*<\/figcaption>)?<\/figure>)|(<p(\s[^>]*)?><a(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span><\/a><\/p>)|(<a(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span><\/a>)|(<p(\s[^>]*)?><span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span><\/p>)|(<span class=\"Db-Media dbtmp-element-protector-wrapper\"><img\s[^>]+\/><span class=\"Db-Media-overlay dbtmp-element-protector-overlay\"><\/span><\/span>)/g"
  )
  let imageSrcRe = %re("/\ssrc=\"([^\"]+)\"/")
  let titleRe = %re("/<figcaption(\s[^>]*)?>([^>]*)<\/figcaption>/")
  let acc = []

  let lastCheckpoint = ref(0)
  let break = ref(false)
  while !break.contents {
    switch imageRe->Js.Re.exec_(transformedContent) {
    | Some(result) =>
      let captures = result->Js.Re.captures
      captures[0]
      ->Option.flatMap(Js.Nullable.toOption)
      ->Option.map(match => {
        let index = result->Js.Re.index
        let before =
          transformedContent
          ->Js.String2.slice(~from=lastCheckpoint.contents, ~to_=index)
          ->Js.String2.replaceByRe(cleanHtmlTagEndRe, "")
          ->Js.String2.replaceByRe(cleanHtmlTagStartRe, "")
          ->Js.String2.trim
        let next = imageRe->Js.Re.lastIndex
        lastCheckpoint.contents = next
        if before->Js.String2.length > 0 {
          acc
          ->Js.Array2.push(
            <div
              className={"DameBioHtml" ++ (" DameBioHtml--" ++ cat->Category.toSlug)}
              dangerouslySetInnerHTML={
                "__html": before,
              }
            />,
          )
          ->ignore
        }
        let result = match->Js.String2.match_(imageSrcRe)
        let src = result->Option.flatMap(result => result[1])
        let result = match->Js.String2.match_(titleRe)
        let title = result->Option.flatMap(result => result[2])
        src
        ->Option.map(src => {
          acc
          ->Js.Array2.push(
            <View
            // @todo, no allowed per rrn
            // accessibilityRole=#figure
              style={Style.viewStyle(
                ~justifyContent=#center,
                ~alignItems=#center,
                ~marginVertical=40.->Style.dp,
                (),
              )}>
              <View
                style={Style.viewStyle(
                  ~maxWidth=imageMaxWidth->Style.dp,
                  ~marginHorizontal=-20.->Style.dp,
                  ~backgroundColor=Consts.Colors.lightGrey,
                  ~borderRadius=3.,
                  ~overflow=#hidden,
                  (),
                )}>
                <View
                  style={Style.array([
                    StyleSheet.absoluteFill,
                    Style.viewStyle(~justifyContent=#center, ()),
                  ])}>
                  <ActivityIndicator size=ActivityIndicator.Size.small color=Consts.Colors.main />
                </View>
                {mediaData
                ->Option.flatMap(m => {
                  let alt =
                    m
                    ->Js.Dict.get(src)
                    ->Option.flatMap(media => media["title"])
                    ->Option.getWithDefault("")
                  m
                  ->Js.Dict.get(src)
                  ->Option.flatMap(media => media["sizes"])
                  ->Option.flatMap(media =>
                    (media->Array.keep(m => m["name"]->Option.getWithDefault("") === "s"))[0]
                  )
                  ->Option.map(media => {
                    let realWidth = media["width"]->Option.getWithDefault(imageFallbackWidth)
                    let realHeight = media["height"]->Option.getWithDefault(imageFallbackWidth)
                    // avoid oversized image
                    let width = min(realWidth, imageMaxWidth)
                    let height = realHeight /. realWidth *. width
                    <Next.Image
                      alt
                      quality=imageQuality
                      // src={media["sourceUrl"]->Option.getWithDefault(src)}
                      src
                      width
                      height
                      unoptimized={Consts.Env.process["env"]["NODE_ENV"] === Consts.Env.dev}
                    />
                  })
                })
                ->Option.getWithDefault(
                  <Next.Image
                    alt=""
                    quality=imageQuality
                    src
                    width=imageFallbackWidth
                    height=imageFallbackHeight
                  />,
                )}
                <View style=StyleSheet.absoluteFill />
              </View>
              {title
              ->Option.map(title => {
                <Text
                  style={Style.textStyle(
                    ~color=Consts.Colors.darkLabel,
                    ~paddingTop=20.->Style.dp,
                    (),
                  )}>
                  {title->React.string}
                </Text>
              })
              ->Option.getWithDefault(React.null)}
            </View>,
          )
          ->ignore
        })
        ->ignore
      })
      ->ignore
    | None => break := true
    }
  }
  if lastCheckpoint.contents < transformedContent->Js.String2.length {
    let after =
      transformedContent
      ->Js.String2.sliceToEnd(~from=lastCheckpoint.contents)
      ->Js.String2.replaceByRe(cleanHtmlTagEndRe, "")
      ->Js.String2.replaceByRe(cleanHtmlTagStartRe, "")
      ->Js.String2.trim
    acc
    ->Js.Array2.push(
      <div
        className={"DameBioHtml" ++ (" DameBioHtml--" ++ cat->Category.toSlug)}
        dangerouslySetInnerHTML={
          "__html": after,
        }
      />,
    )
    ->ignore
  }
  acc
  ->Array.mapWithIndex((index, item) => React.cloneElement(item, {"key": index->Int.toString}))
  ->React.array
}
