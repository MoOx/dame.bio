open Belt;

let component = ReasonReact.statelessComponent("DameBioHtml");

let make = (~content, _) => {
  ...component,
  render: _self => {
    <div
      className="DameBioHtml"
      dangerouslySetInnerHTML={
        "__html":
          content->Option.getWithDefault("")
          /* make images url absolute */
          |> Js.String.replaceByRe(
               [%re "/=\"\\/wp-content/g"],
               "=\"https://dame.bio/wp-content",
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
               ""
               ++ "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 60px auto; width: 80%;\">"
               ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
               ++ "<img src=\"/images/separator-hearts.png\" style=\"margin: 0 10px; width: 48px; height: 15px;\" alt=\"\" />"
               ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
               ++ "</span>",
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
  },
};
