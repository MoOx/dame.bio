open Belt;
open BsReactNative;

let imageRatio = 240. /. 350.;

let styles =
  StyleSheet.create(
    Style.{
      "block":
        style([
          flex(1.),
          padding(Pt(20.)),
          borderColor(String("#F0F0EF")),
          backgroundColor(String("#fff")),
        ]),
      "metaRow": style([flexDirection(Row), justifyContent(SpaceBetween)]),
      "metaRowLeft": style([flexDirection(Row), alignItems(Baseline)]),
      "date":
        style([fontSize(Float(12.)), color(String(Consts.Colors.grey))]),
      "title":
        style([
          marginBottom(Pt(10.)),
          fontSize(Float(32.)),
          lineHeight(32. *. 1.5),
          color(String("#006579")),
          fontWeight(`_300),
        ]),
      "categoryText":
        style([fontSize(Float(14.)), color(String("#DE6D88"))]),
      "actions":
        style([
          flexDirection(Row),
          alignSelf(FlexEnd),
          alignItems(Center),
        ]),
      "action": style([flexDirection(Row)]),
      "actionText":
        style([
          fontSize(Float(10.)),
          color(String(ButtonLike.defaultColor)),
        ]),
      "link": style([padding(Pt(10.))]),
      "tags":
        style([
          flexDirection(Row),
          flexWrap(Wrap),
          justifyContent(Center),
        ]),
      "tagText":
        style([
          fontSize(Float(16.)),
          lineHeight(29.),
          color(String("#006579")),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("PageDetail");

let make = (~item, _) => {
  ...component,
  render: _self => {
    <ViewWeb style=styles##block accessibilityRole="article">
      <BsReactHelmet>
        <style>
          {j|
.dbPage {
  font-size: 16px;
  line-height: 29px;
  color: #49443A;
}
.dbPage a {
  color: #3ba013;
}
.dbPage strong {
  font-weight: 800;
}
.dbPage img {
  max-width: 100%;
}

.dbPage .ingredients dt,
.dbPage h2 {
  font-weight: 800;
  font-size: 20px;
  margin: 40px 0 20px;
}

.dbPage .ingredients dt::before,
.dbPage h2::before {
  content: "☆ ";
}

.dbPage dd { margin: 0 }

.wp-block-image {
  margin: 8% auto;
  max-width: 90%;
}

.wp-block-image figcaption {
  color: #555d66;
  font-size: 14px;
  margin-top: 10px;
  text-align: center;
}

.dbtmp-element-protector-wrapper {
  position: relative;
  display: block;
  margin: 0;
}
.dbtmp-element-protector-wrapper img {display: block;}
.dbtmp-element-protector-overlay {position:absolute;top:0;left:0;right:0;bottom:0;}
|j}
          ->ReasonReact.string
        </style>
      </BsReactHelmet>
      <TextWeb style=styles##title accessibilityRole="heading">
        <span
          dangerouslySetInnerHTML={
            "__html": item##title->Option.getWithDefault(""),
          }
        />
      </TextWeb>
      <Spacer />
      <SpacedView>
        <div
          className="dbPage"
          dangerouslySetInnerHTML={
            "__html":
              item##content->Option.getWithDefault("")
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
        />
      </SpacedView>
    </ViewWeb>;
  },
};
