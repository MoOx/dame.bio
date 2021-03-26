open Belt;
open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "row": style(~flexDirection=`row, ()),
      "comment": style(~flexDirection=`row, ()),
      "commentAvatar":
        style(
          ~width=40.->dp,
          ~height=40.->dp,
          ~borderRadius=Consts.Radius.avatar,
          (),
        ),
      "commentAvatarDefault":
        style(
          ~lineHeight=40.,
          ~color="#fff",
          ~textAlign=`center,
          ~fontWeight=`_600,
          ~fontSize=18.,
          (),
        ),
      "commentAvatarImage":
        style(
          ~position=`absolute,
          ~top=0.->dp,
          ~left=0.->dp,
          ~width=40.->dp,
          ~height=40.->dp,
          ~borderRadius=Consts.Radius.avatar,
          (),
        ),
      "commentTextContainer": style(~flex=1., ()),
      "commentMeta": style(~flexDirection=`row, ()),
      "commentAuthor": style(),
      "commentAuthorText":
        style(
          ~color=Consts.Colors.darkLabel,
          ~fontWeight=`_600,
          ~lineHeight=24.,
          ~textDecorationLine=`none,
          (),
        ),
      "commentOwner":
        style(
          ~backgroundColor=Consts.Colors.pink,
          ~paddingHorizontal=6.->dp,
          ~borderRadius=Consts.Radius.box,
          ~alignSelf=`center,
          (),
        ),
      "commentOwnerText":
        style(
          ~color="#fff",
          ~fontSize=10.,
          ~fontWeight=`_300,
          ~lineHeight=20.,
          (),
        ),
      "commentDate":
        style(~fontSize=11., ~lineHeight=24., ~color="#bdbdbd", ()),
      "commentContent":
        style(
          ~flexShrink=1.,
          ~color=Consts.Colors.darkLabel,
          ~fontSize=14.,
          ~lineHeight=24.,
          (),
        ),
    })
  );

[@react.component]
let make = (~comment, ~separator, ~canReply, ~onReply=_ => (), ()) => {
  let name =
    (
      switch (comment##author) {
      | Some(`CommentAuthor(a)) => a##name
      | Some(`User(a)) => a##name
      | None => Some("")
      }
    )
    ->Option.getWithDefault("");
  let url =
    (
      switch (comment##author) {
      | Some(`CommentAuthor(a)) => a##url
      | Some(`User(a)) => a##url
      | None => None
      }
    )
    ->Option.getWithDefault("");
  <>
    {separator ? <> <CommentSeparator /> <Spacer /> </> : React.null}
    <View style=styles##comment>
      {comment##parent->Option.isSome ? <Spacer size=XL /> : React.null}
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
               ->Option.getWithDefault("")
               ->Md5.make
            ++ "?s=96&d=mm&r=g&d=blank"
          }
        />
      </View>
      <Spacer size=XS />
      <View style=styles##commentTextContainer>
        <View style=styles##commentMeta>
          {String.length(url) > 0
             ? <ViewLink style=styles##commentAuthor href=url>
                 <Text style=styles##commentAuthorText>
                   name->React.string
                 </Text>
               </ViewLink>
             : <Text style=styles##commentAuthor> name->React.string </Text>}
          {switch (comment##author) {
           | Some(`User(a)) when a##userId->Option.getWithDefault(0) == 2 =>
             <>
               <Text> " "->React.string </Text>
               <ViewLink href=url style=styles##commentOwner>
                 <Text style=styles##commentOwnerText>
                   "Auteur"->React.string
                 </Text>
               </ViewLink>
             </>
           | _ => React.null
           }}
        </View>
        <View style=styles##row>
          <Text style=styles##commentDate>
            {comment##dateGmt
             ->Option.mapWithDefault(Js.Date.make(), d =>
                 Js.Date.fromString(d |> Js.String.replace(" ", "T"))
               )
             ->Date.relativeDate
             ->String.capitalize_ascii
             ++ {j|  ·  |j}
             |> React.string}
          </Text>
          {canReply
             ? <TouchableOpacity onPress=onReply>
                 <Text style=styles##commentDate>
                   {j|Répondre|j}->React.string
                 </Text>
               </TouchableOpacity>
             : React.null}
        </View>
        <Text style=styles##commentContent>
          <div
            className="dbComment"
            dangerouslySetInnerHTML={
              "__html":
                comment##content->Option.getWithDefault("")
                |> Js.String.replace("<p>", "")
                |> Js.String.replace("</p>", ""),
            }
          />
        </Text>
      </View>
    </View>
    <Spacer />
  </>;
};
