open BsReactNative;

let component = ReasonReact.statelessComponent("Comment");

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
      "commentAuthor": style([]),
      "commentAuthorText":
        style([
          color(String("#49443A")),
          fontWeight(`_600),
          lineHeight(24.),
          textDecorationLine(Style.None),
        ]),
      "commentOwner":
        style([
          backgroundColor(String("#DE6D88")),
          paddingHorizontal(Pt(6.)),
          borderRadius(8.),
          alignSelf(Center),
        ]),
      "commentOwnerText":
        style([
          color(String("#fff")),
          fontSize(Float(10.)),
          fontWeight(`_300),
          lineHeight(20.),
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

let make = (~comment, ~separator, ~canReply, ~onReply=() => (), _) => {
  ...component,
  render: _self => {
    let name =
      (
        switch (comment##author) {
        | Some(`CommentAuthor(a)) => a##name
        | Some(`User(a)) => a##name
        | None => Some("")
        }
      )
      ->Belt.Option.getWithDefault("");
    let url =
      (
        switch (comment##author) {
        | Some(`CommentAuthor(a)) => a##url
        | Some(`User(a)) => a##url
        | None => None
        }
      )
      ->Belt.Option.getWithDefault("");
    <>
      {separator ? <> <CommentSeparator /> <Spacer /> </> : ReasonReact.null}
      <View style=styles##comment>
        {comment##parent->Belt.Option.isSome ?
           <Spacer size=XL /> : ReasonReact.null}
        <View>
          <Spacer size=XXS />
          <Avatar
            name
            url={
              "https://secure.gravatar.com/avatar/"
              ++ (
                   switch (comment##author) {
                   | Some(`CommentAuthor(a)) => a##email
                   | Some(`User(a)) => a##email
                   | None => Some("")
                   }
                 )
                 ->Belt.Option.getWithDefault("")
                 ->Md5.make
              ++ "?s=96&d=mm&r=g&d=blank"
            }
          />
        </View>
        <Spacer size=XS />
        <View style=styles##commentTextContainer>
          <View style=styles##commentMeta>
            {String.length(url) > 0 ?
               <TouchableOpacityLink style=styles##commentAuthor href=url>
                 <Text style=styles##commentAuthorText>
                   name->ReasonReact.string
                 </Text>
               </TouchableOpacityLink> :
               <Text style=styles##commentAuthor>
                 name->ReasonReact.string
               </Text>}
            {switch (comment##author) {
             | Some(`User(a))
                 when a##userId->Belt.Option.getWithDefault(0) == 2 =>
               <>
                 <Text> " "->ReasonReact.string </Text>
                 <TouchableOpacityLink href=url style=styles##commentOwner>
                   <Text style=styles##commentOwnerText>
                     "Auteur"->ReasonReact.string
                   </Text>
                 </TouchableOpacityLink>
               </>
             | _ => ReasonReact.null
             }}
          </View>
          <View style=styles##row>
            <Text style=styles##commentDate>
              {comment##dateGmt
               ->Belt.Option.mapWithDefault(Js.Date.make(), d =>
                   Js.Date.fromString(d |> Js.String.replace(" ", "T"))
                 )
               ->Date.relativeDate
               ->String.capitalize
               ++ {j|  ·  |j}
               |> ReasonReact.string}
            </Text>
            {canReply ?
               <TouchableOpacity onPress=onReply>
                 <Text style=styles##commentDate>
                   {j|Répondre|j}->ReasonReact.string
                 </Text>
               </TouchableOpacity> :
               ReasonReact.null}
          </View>
          <Text style=styles##commentContent>
            <div
              className="dbComment"
              dangerouslySetInnerHTML={
                "__html":
                  comment##content->Belt.Option.getWithDefault("")
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
