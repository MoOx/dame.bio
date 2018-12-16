open Helpers;

open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "row": style([flexDirection(Row)]),
      "comment": style([flexDirection(Row)]),
      "commentAvatar":
        style([width(Pt(40.)), height(Pt(40.)), borderRadius(100.)]),
      "commentAvatarDefault":
        style([
          lineHeight(40.),
          color(String("#fff")),
          textAlign(Center),
          fontWeight(`_600),
          fontSize(Float(18.)),
        ]),
      "commentAvatarImage":
        style([
          position(Absolute),
          top(Pt(0.)),
          left(Pt(0.)),
          width(Pt(40.)),
          height(Pt(40.)),
          borderRadius(100.),
        ]),
      "commentTextContainer": style([flex(1.)]),
      "commentMeta": style([flexDirection(Row)]),
      "commentAuthor":
        style([
          color(String("#49443A")),
          fontWeight(`_600),
          lineHeight(24.),
          textDecorationLine(Style.None),
        ]),
      "commentOwner":
        style([
          color(String("#fff")),
          backgroundColor(String("#DE6D88")),
          paddingHorizontal(Pt(6.)),
          borderRadius(8.),
          fontSize(Float(10.)),
          fontWeight(`_300),
          lineHeight(20.),
          alignSelf(Center),
        ]),
      "commentDate":
        style([
          fontSize(Float(11.)),
          lineHeight(24.),
          color(String("#bdbdbd")),
        ]),
      "commentContent":
        style([
          flexShrink(1.),
          color(String("#49443A")),
          fontSize(Float(14.)),
          lineHeight(24.),
        ]),
    },
  );

let component = ReasonReact.statelessComponent("Comment");

let make =
    (
      ~comment: Structures.comment,
      ~separator,
      ~canReply,
      ~onReply=() => (),
      _,
    ) => {
  ...component,
  render: _self => {
    let isOwner = comment.author == 2;
    <>
      {separator ? <> <CommentSeparator /> <Spacer /> </> : nothing}
      <View style=styles##comment>
        {comment.parent > 0 ? <Spacer size=XL /> : nothing}
        <View>
          <Spacer size=XXS />
          <Avatar
            name={comment.author_name}
            url={comment.author_avatar_url ++ "&d=blank"}
          />
        </View>
        <Spacer size=XS />
        <View style=styles##commentTextContainer>
          <View style=styles##commentMeta>
            {String.length(comment.author_url) > 0 ?
               <TextLink style=styles##commentAuthor href={comment.author_url}>
                 {comment.author_name |> text}
               </TextLink> :
               <Text style=styles##commentAuthor>
                 {comment.author_name |> text}
               </Text>}
            {isOwner ?
               <>
                 <Text> {" " |> text} </Text>
                 <TextLink
                   href={comment.author_url} style=styles##commentOwner>
                   {"Auteur" |> text}
                 </TextLink>
               </> :
               nothing}
          </View>
          <View style=styles##row>
            <Text style=styles##commentDate>
              {(comment.date |> Date.relativeDate |> String.capitalize)
               ++ {j|  ·  |j}
               |> text}
            </Text>
            {canReply ?
               <TouchableOpacity onPress=onReply>
                 <Text style=styles##commentDate>
                   {{j|Répondre|j} |> text}
                 </Text>
               </TouchableOpacity> :
               nothing}
          </View>
          <Text style=styles##commentContent>
            <div
              className="dbComment"
              dangerouslySetInnerHTML={
                "__html":
                  comment.content
                  |> Js.String.replace("<p>", "")
                  |> Js.String.replace("</p>", ""),
              }
            />
          </Text>
        </View>
      </View>
      <Spacer />
    </>;
  },
};
