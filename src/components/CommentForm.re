open BsReactNative;

open Helpers;

let opaque = 1.;
let transparent = 0.;
let yVisible = 0.;
let yHidden = 40.;

let animateFormMeta =
    (~showPreview, ~previewOpacity, ~previewY, ~textInputOpacity, ~textInputY) =>
  Animated.start(
    Animated.parallel(
      [|
        Animated.spring(
          ~value=previewOpacity,
          ~toValue=`raw(showPreview ? opaque : transparent),
          (),
        ),
        Animated.spring(
          ~value=previewY,
          ~toValue=`raw(showPreview ? yVisible : yHidden),
          (),
        ),
        Animated.spring(
          ~value=textInputOpacity,
          ~toValue=`raw(showPreview ? transparent : opaque),
          (),
        ),
        Animated.spring(
          ~value=textInputY,
          ~toValue=`raw(showPreview ? -. yHidden : yVisible),
          (),
        ),
      |],
      {"stopTogether": true},
    ),
    (),
  );

let styles =
  StyleSheet.create(
    Style.{
      "container": style([flex(1.)]),
      "row": style([flex(1.), flexDirection(Row), flexWrap(Wrap)]),
      "avatar":
        style([
          /* compensate TextInput borderWidth */
          paddingVertical(Pt(2.)),
        ]),
      "commentBox": style([flex(1.)]),
      "metaPreview": style([]),
      "metaPreviewName":
        style([
          color(String("#49443A")),
          fontWeight(`_600),
          lineHeight(24.),
          textDecorationLine(Style.None),
        ]),
      "metaPreviewEdit":
        style([
          fontSize(Float(11.)),
          lineHeight(24.),
          color(String("#bdbdbd")),
        ]),
      "textInputs": style([]),
      "textInputWrapper": style([flex(1.), paddingBottom(Pt(10.))]),
      "textInput":
        style([
          color(String("#49443A")),
          backgroundColor(String("#fff")),
          fontSize(Float(14.)),
          lineHeight(16.),
          margin(Pt(0.)),
          paddingVertical(Pt(10.)),
          paddingHorizontal(Pt(12.)),
          borderWidth(1.),
          borderColor(String("#ddd")),
        ]),
      "textInputError": style([borderColor(String("#e07676"))]),
      "textInputName":
        style([
          fontWeight(`_600),
          borderTopLeftRadius(16.),
          borderBottomLeftRadius(16.),
        ]),
      "textInputEmail": style([]),
      "textInputUrl":
        style([borderTopRightRadius(16.), borderBottomRightRadius(16.)]),
      "textInputCommentRow": style([zIndex(1)]),
      "textInputComment":
        style([
          paddingLeft(Pt(12.)),
          paddingRight(Pt(80.)),
          borderRadius(16.),
        ]),
      "buttonSend":
        style([
          zIndex(1),
          position(Absolute),
          top(Pt(29.)),
          right(Pt(10.)),
          padding(Pt(10.)),
        ]),
      "buttonSendText":
        style([fontSize(Float(14.)), color(String("#2096F3"))]),
      "errorText":
        style([
          position(Absolute),
          bottom(Pt(-4.)),
          paddingVertical(Pt(2.)),
          paddingHorizontal(Pt(13.)),
          fontSize(Float(10.)),
          color(String("#e07676")),
        ]),
    },
  );

type comment = {
  author: int,
  email: string,
  name: string,
  url: string,
  content: string,
  editMeta: bool,
};

let newComment = (): comment => {
  let name =
    switch (localGet("name")) {
    | None => ""
    | Some(v) => v
    };
  let email =
    switch (localGet("email")) {
    | None => ""
    | Some(v) => v
    };
  let url =
    switch (localGet("url")) {
    | None => ""
    | Some(v) => v
    };
  {
    /* todo read user id from local _*/
    author: 0,
    name,
    email,
    url,
    content: "",
    editMeta: false /*String.length(name) == 0 || String.length(email) == 0,*/
  };
};

type errors = {
  message: string,
  email: option(string),
};

type computedErrors = {
  name: option(string),
  email: option(string),
  content: option(string),
};

let noErrors = {name: None, email: None, content: None};

type action =
  | CommentEdit(comment)
  | CommentSend(comment)
  | CommentSuccess((comment, Structures.comment))
  | CommentError((comment, errors));

type commentState =
  | New
  | InProgress(comment)
  | Sent((comment, Js.Json.t))
  | Posted((comment, Structures.comment))
  | Errored((comment, errors));

type animatedState = {
  metaPreviewOpacity: Animated.Value.t,
  metaPreviewY: Animated.Value.t,
  metaTextInputOpacity: Animated.Value.t,
  metaTextInputY: Animated.Value.t,
};

type state = {
  comment: commentState,
  animated: animatedState,
};

let sendComment = (commentToSend, success, failure) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      apiBaseUrl ++ "wp-json/wp/v2/comments",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(commentToSend)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(response =>
         all2((
           resolve(Fetch.Response.status(response)),
           Fetch.Response.json(response),
         ))
       )
    |> then_(((status, json)) =>
         if (status == 201) {
           Structures.decodeComment(json)->success->resolve;
         } else {
           json
           ->Obj.magic
           ->(
               json =>
                 Json.Decode.{
                   email:
                     json
                     |> optional(
                          at(["data", "params", "author_email"], string),
                        ),
                   message: json |> field("message", string),
                 }
             )
           ->failure
           ->resolve;
         }
       )
    |> catch(err => {
         Js.log(err);
         failure({message: "Oups, une erreur est survenue!", email: None})
         |> resolve;
       })
  );

let component = ReasonReact.reducerComponent("CommentForm");

let make = (~postId, ~parentCommentId, _children) => {
  ...component,
  initialState: () => {
    comment: New,
    animated: {
      metaPreviewOpacity: Animated.Value.create(transparent),
      metaPreviewY: Animated.Value.create(yHidden),
      metaTextInputOpacity: Animated.Value.create(transparent),
      metaTextInputY: Animated.Value.create(-. yHidden),
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | CommentEdit(comment) =>
      switch (state.comment) {
      /* unless we are currently waiting for server reply for a comment
         we just allow edition of the comment, even if status is errored */
      /* | New */
      /* | InProgress(comment) */
      /* | Posted((comment, commentSuccessReponse)) */
      | Sent(_) =>
        Js.log("You can't edit while posting");
        ReasonReact.NoUpdate;
      /* | Errored((comment, string)) */
      | _ => ReasonReact.Update({...state, comment: InProgress(comment)})
      }
    | CommentSend(comment) =>
      switch (state.comment) {
      | New =>
        ReasonReact.Update({
          ...state,
          comment:
            Errored((
              comment,
              {message: {j|Vous n'avez encore rien écrit|j}, email: None},
            )),
        })
      /* | InProgress(comment) */
      | Sent(_) =>
        Js.log("You can't post while posting already");
        ReasonReact.NoUpdate;
      | Posted(_) =>
        /* impossible state as you cannot have access to CommentSend while state is Posted */
        ReasonReact.NoUpdate
      | Errored((_, _)) => ReasonReact.NoUpdate
      | _ =>
        /* https://developer.wordpress.org/rest-api/reference/comments/#arguments */
        /* todo see how to validate this payload type, with commentToSend or similar */
        let pl = Js.Dict.empty();
        /* to avoid rest_comment_author_invalid */
        if (comment.author > 0) {
          Js.Dict.set(
            pl,
            "author",
            Js.Json.number(float_of_int(comment.author)),
          );
        };
        Js.Dict.set(pl, "author_email", Js.Json.string(comment.email));
        Js.Dict.set(pl, "author_name", Js.Json.string(comment.name));
        Js.Dict.set(pl, "author_url", Js.Json.string(comment.url));
        Js.Dict.set(
          pl,
          "author_user_agent",
          Js.Json.string([%raw "navigator.userAgent"]),
        );
        Js.Dict.set(pl, "content", Js.Json.string(comment.content));
        /* wordpress doesnt' store date as complete ISO, so we have to sent GMT+1 and GMT (according to site TZ - which is GMT+1) */
        Js.Dict.set(
          pl,
          "date",
          (Js.Date.now() +. 1000. *. 60. *. 60.)
          ->Js.Date.fromFloat
          ->Js.Date.toISOString
          ->String.sub(0, 19)
          ->Js.Json.string,
        );
        Js.Dict.set(
          pl,
          "date_gmt",
          Js.Date.now()
          ->Js.Date.fromFloat
          ->Js.Date.toISOString
          ->String.sub(0, 19)
          ->Js.Json.string,
        );
        Js.Dict.set(
          pl,
          "parent",
          Js.Json.number(float_of_int(parentCommentId)),
        );
        Js.Dict.set(pl, "post", Js.Json.number(float_of_int(postId)));
        let payload = Js.Json.object_(pl);
        ReasonReact.UpdateWithSideEffects(
          {...state, comment: Sent((comment, payload))},
          ({send}) =>
            sendComment(
              payload,
              response => send(CommentSuccess((comment, response))),
              error => send(CommentError((comment, error))),
            )
            |> ignore,
        );
      }
    | CommentSuccess((comment, response)) =>
      ReasonReact.Update({...state, comment: Posted((comment, response))})
    | CommentError((comment, err)) =>
      ReasonReact.Update({...state, comment: Errored((comment, err))})
    },
  didUpdate: ({oldSelf, newSelf}) => {
    let (animate, showPreview) =
      switch (oldSelf.state.comment, newSelf.state.comment) {
      | (New, InProgress(newComment)) => (
          true,
          String.length(newComment.name) > 0
          && String.length(newComment.email) > 0,
        )
      | (New, Errored((newComment, _))) => (
          true,
          String.length(newComment.name) > 0
          && String.length(newComment.email) > 0,
        )
      | (InProgress(oldComment), InProgress(newComment))
          when oldComment.editMeta != newComment.editMeta => (
          true,
          !newComment.editMeta,
        )
      | (Errored(_), InProgress(newComment)) when newComment.editMeta => (
          true,
          !newComment.editMeta,
        )
      | _ => (false, false)
      };
    if (animate) {
      animateFormMeta(
        ~showPreview,
        ~previewOpacity=newSelf.state.animated.metaPreviewOpacity,
        ~previewY=newSelf.state.animated.metaPreviewY,
        ~textInputOpacity=newSelf.state.animated.metaTextInputOpacity,
        ~textInputY=newSelf.state.animated.metaTextInputY,
      );
    };
  },

  render: ({state, send}) => {
    let errors =
      switch (state.comment) {
      | New => noErrors
      | InProgress(_) => noErrors
      | Sent((_, _)) => noErrors
      | Posted((_, _)) => noErrors
      | Errored((comment, errors)) =>
        let email =
          String.length(comment.email) == 0 ? Some("Requis") : errors.email;
        let name = String.length(comment.name) == 0 ? Some("Requis") : None;
        let content =
          switch (name, email) {
          | (None, None) when String.length(comment.content) == 0 =>
            Some({j|Vous n'avez encore rien écrit|j})
          | (None, None) => Some(errors.message)
          | _ when String.length(comment.content) == 0 =>
            Some({j|Vous n'avez encore rien écrit|j})
          | _ => None
          };
        {email, name, content};
      };
    switch (errors.name, errors.email) {
    | (Some(_), Some(_)) =>
      animateFormMeta(
        ~showPreview=false,
        ~previewOpacity=state.animated.metaPreviewOpacity,
        ~previewY=state.animated.metaPreviewY,
        ~textInputOpacity=state.animated.metaTextInputOpacity,
        ~textInputY=state.animated.metaTextInputY,
      )
    | _ => ()
    };

    let comment =
      switch (state.comment) {
      | New => newComment()
      | InProgress(comment) => comment
      | Sent((comment, _)) => comment
      | Posted((_, _)) => newComment()
      | Errored((comment, _)) => comment
      };
    /* let disabled =
       switch (state) {
       | Sent((_, _)) => true
       | _ => false
       }; */
    <View>
      <noscript>
        <Text>
          {{j|🚨 Veuillez |j} |> text}
          <a
            target="_blank"
            href="https://www.qwant.com/?q=comment%20activer%20javascript">
            {{j|activer JavaScript|j} |> text}
          </a>
          {{j| pour poster un commentaire.|j} |> text}
        </Text>
        <Spacer />
      </noscript>
      {switch (state.comment) {
       | Sent((_, _)) => <> <ActivityIndicator size=`small /> <Spacer /> </>
       | Posted((_, _)) =>
         <>
           <Text> {{j|👍 Commentaire envoyé!|j} |> text} </Text>
           <Spacer />
         </>
       | _ => nothing
       }}
      <View style=styles##row>
        {parentCommentId > 0 ? <Spacer size=XL /> : nothing}
        <View style=styles##container>
          {<View style=styles##row>
             <View style=styles##avatar>
               <Spacer />
               <Spacer size=XXS />
               <Avatar
                 name={comment.name}
                 url={
                   "https://secure.gravatar.com/avatar/"
                   ++ Md5.make(comment.email)
                   ++ "?s=96&d=mm&r=g&d=blank"
                 }
               />
             </View>
             <Spacer size=XS />
             <View style=styles##commentBox>
               <Animated.View
                 style=Style.(
                   concat([
                     styles##metaPreview,
                     style([
                       opacity(Animated(state.animated.metaPreviewOpacity)),
                       Transform.makeAnimated(
                         ~translateY=state.animated.metaPreviewY,
                         (),
                       ),
                     ]),
                   ])
                 )>
                 <View style=styles##row>
                   <Spacer size=S />
                   {String.length(comment.url) > 0 ?
                      <TextLink
                        style=styles##metaPreviewName href={comment.url}>
                        {comment.name |> text}
                      </TextLink> :
                      <Text style=styles##metaPreviewName>
                        {comment.name |> text}
                      </Text>}
                   <TouchableOpacity
                     onPress={() =>
                       send(CommentEdit({...comment, editMeta: true}))
                       |> ignore
                     }>
                     <Text style=styles##metaPreviewEdit>
                       {{j|  ·  |j} |> text}
                       {{j|Modifier|j} |> text}
                     </Text>
                   </TouchableOpacity>
                 </View>
                 <Spacer size=XXS />
               </Animated.View>
               <View
                 style={Style.concat([
                   styles##textInputCommentRow,
                   styles##textInputWrapper,
                 ])}>
                 <TextInputAutoMultilines
                   style=Style.(
                     concat([
                       styles##textInput,
                       switch (errors.content) {
                       | Some(_) => styles##textInputError
                       | None => style([])
                       },
                       styles##textInputComment,
                     ])
                   )
                   value={comment.content}
                   placeholder={
                     "Ajouter un commentaire "
                     ++ (
                       !comment.editMeta && String.length(comment.name) > 0 ?
                         "en tant que " ++ comment.name : ""
                     )
                     ++ "..."
                   }
                   onChangeText={text =>
                     send(
                       CommentEdit({
                         ...comment,
                         content: text,
                         editMeta:
                           String.length(comment.name) == 0
                           || String.length(comment.email) == 0,
                       }),
                     )
                   }
                   onFocus={() => {
                     let shouldEditComment =
                       switch (state.comment) {
                       | New => true
                       | InProgress(_) => false
                       | Sent((_, _)) => false
                       | Posted((_, _)) => false
                       | Errored((_, _)) => false
                       };
                     (
                       if (shouldEditComment) {
                         send(
                           CommentEdit({
                             ...comment,
                             editMeta:
                               String.length(comment.name) == 0
                               || String.length(comment.email) == 0,
                           }),
                         );
                       }
                     )
                     |> ignore;
                   }}
                 />
                 {switch (errors.content) {
                  | Some(message) =>
                    <Text style=styles##errorText> {message |> text} </Text>
                  | None => nothing
                  }}
               </View>
               <Spacer size=XXS />
               <Animated.View
                 style=Style.(
                   concat([
                     styles##textInputs,
                     style([
                       opacity(
                         Animated(state.animated.metaTextInputOpacity),
                       ),
                       Transform.makeAnimated(
                         ~translateY=state.animated.metaTextInputY,
                         (),
                       ),
                     ]),
                   ])
                 )>
                 <View style=styles##row>
                   <View style=styles##textInputWrapper>
                     <TextInput
                       style=Style.(
                         concat([
                           styles##textInput,
                           switch (errors.name) {
                           | Some(_) => styles##textInputError
                           | None => style([])
                           },
                           styles##textInputName,
                         ])
                       )
                       value={comment.name}
                       placeholder="Nom *"
                       onChangeText={text => {
                         localSave("name", text);
                         send(CommentEdit({...comment, name: text}));
                       }}
                     />
                     {switch (errors.name) {
                      | Some(message) =>
                        <Text style=styles##errorText>
                          {message |> text}
                        </Text>
                      | None => nothing
                      }}
                   </View>
                   <Spacer size=XXS />
                   <View style=styles##textInputWrapper>
                     <TextInput
                       style=Style.(
                         concat([
                           styles##textInput,
                           switch (errors.email) {
                           | Some(_) => styles##textInputError
                           | None => style([])
                           },
                           styles##textInputEmail,
                         ])
                       )
                       value={comment.email}
                       placeholder="Email *"
                       onChangeText={text => {
                         localSave("email", text);
                         send(CommentEdit({...comment, email: text}));
                       }}
                     />
                     {switch (errors.email) {
                      | Some(message) =>
                        <Text style=styles##errorText>
                          {message |> text}
                        </Text>
                      | None => nothing
                      }}
                   </View>
                   <Spacer size=XXS />
                   <View style=styles##textInputWrapper>
                     <TextInput
                       style=Style.(
                         concat([styles##textInput, styles##textInputUrl])
                       )
                       value={comment.url}
                       placeholder="https://site.web"
                       onChangeText={text => {
                         localSave("url", text);
                         send(CommentEdit({...comment, url: text}));
                       }}
                     />
                   </View>
                 </View>
               </Animated.View>
               <TouchableOpacity
                 onPress={() => send(CommentSend(comment))}
                 style=styles##buttonSend>
                 <Text style=styles##buttonSendText>
                   {"Envoyer" |> text}
                 </Text>
               </TouchableOpacity>
             </View>
           </View>}
        </View>
      </View>
    </View>;
  },
};
