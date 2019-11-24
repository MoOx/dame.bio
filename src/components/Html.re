open Belt;

[@react.component]
let make = (~content, ~category=?, ()) => {
  let cat = category->Category.from;
  <div
    className={"DameBioHtml" ++ " DameBioHtml--" ++ cat->Category.toSlug}
    dangerouslySetInnerHTML={
      "__html":
        content->Option.getWithDefault("")
        /* make images url absolute */
        |> Js.String.replaceByRe(
             [%re "/=\"\\/wp-content/g"],
             "=\"" ++ Consts.backendUrl ++ "wp-content",
           )
        /* custom behavior decided for us "white star unicode" => a png */
        |> Js.String.replaceByRe(
             [%re "/<p style=\"text-align:center\">☆<\\/p>/g"],
             ""
             ++ "<span style=\"display: block; text-align: center; margin: 40px;\">"
             ++ "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />"
             ++ "</span>",
           )
        /* custom behavior decided for us hr => a png */
        |> Js.String.replaceByRe(
             [%re "/<hr ?(class=\"wp-block-separator\")? ?\\/?>/g"],
             Separator.makeAsString(cat),
           )
        /* custom behavior decided for us --- => a png */
        |> Js.String.replaceByRe(
             [%re "/<p style=\"text-align:center\">---<\\/p>/g"],
             ""
             ++ "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 40px auto; width: 80%;\">"
             ++ "<img src=\"/images/separator-long-head.png\" style=\"width: 14.5px; height: 7.5px; margin: 1px 0 0 0;\" alt=\"\" />"
             ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
             ++ "<img src=\"/images/separator-long-tail.png\" style=\"width: 64px; height: 19.5px;\" alt=\"\" />"
             ++ "</span>",
           ),
    }
  />;
};
