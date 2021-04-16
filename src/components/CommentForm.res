open Belt
open ReactNative

let opaque = 1.
let transparent = 0.
let yVisible = 0.
let yHidden = 40.

let animateFormMeta = (~showPreview, ~previewOpacity, ~previewY, ~textInputOpacity, ~textInputY) =>
  Animated.start(
    Animated.parallel(
      [
        previewOpacity->Animated.spring(
          Animated.Value.Spring.config(
            ~useNativeDriver=true,
            ~toValue=(showPreview ? opaque : transparent)->Animated.Value.Spring.fromRawValue,
            (),
          ),
        ),
        previewY->Animated.spring(
          Animated.Value.Spring.config(
            ~useNativeDriver=true,
            ~toValue=(showPreview ? yVisible : yHidden)->Animated.Value.Spring.fromRawValue,
            (),
          ),
        ),
        textInputOpacity->Animated.spring(
          Animated.Value.Spring.config(
            ~useNativeDriver=true,
            ~toValue=(showPreview ? transparent : opaque)->Animated.Value.Spring.fromRawValue,
            (),
          ),
        ),
        textInputY->Animated.spring(
          Animated.Value.Spring.config(
            ~useNativeDriver=true,
            ~toValue=(showPreview ? -.yHidden : yVisible)->Animated.Value.Spring.fromRawValue,
            (),
          ),
        ),
      ],
      {stopTogether: true},
    ),
    (),
  )

let styles = {
  open Style
  StyleSheet.create({
    "container": style(~flex=1., ()),
    "row": style(~flexGrow=1., ~flexShrink=1., ~flexDirection=#row, ~flexWrap=#wrap, ()),
    "avatar": style(
      /* compensate TextInput borderWidth */
      ~paddingVertical=2.->dp,
      (),
    ),
    "commentBox": style(~flex=1., ()),
    "metaPreview": style(),
    "metaPreviewName": style(
      ~color=Consts.Colors.darkLabel,
      ~fontWeight=#_600,
      ~lineHeight=24.,
      ~textDecorationLine=#none,
      (),
    ),
    "metaPreviewEdit": style(~fontSize=11., ~lineHeight=24., ~color="#bdbdbd", ()),
    "textInputs": style(),
    "textInputWrapper": style(~flexGrow=1., ~flexShrink=1., ~paddingBottom=10.->dp, ()),
    "textInput": style(
      ~color=Consts.Colors.darkLabel,
      ~backgroundColor="#fff",
      /* Don't go lower than 16 to avoid Safari iOS to zoom on the page */
      ~fontSize=16.,
      ~lineHeight=16.,
      ~margin=0.->dp,
      ~paddingVertical=10.->dp,
      ~paddingHorizontal=12.->dp,
      ~borderWidth=1.,
      ~borderColor="#ddd",
      (),
    ),
    "textInputError": style(~borderColor="#e07676", ()),
    "textInputName": style(
      ~fontWeight=#_600,
      ~borderTopLeftRadius=16.,
      ~borderBottomLeftRadius=16.,
      (),
    ),
    "textInputEmail": style(),
    "textInputUrl": style(~borderTopRightRadius=16., ~borderBottomRightRadius=16., ()),
    "textInputCommentRow": style(~zIndex=1, ()),
    "textInputComment": style(
      ~paddingLeft=12.->dp,
      ~paddingRight=80.->dp,
      ~borderRadius=Consts.Radius.field,
      (),
    ),
    "buttonSend": style(
      ~zIndex=1,
      ~position=#absolute,
      ~top=29.->dp,
      ~right=10.->dp,
      ~padding=10.->dp,
      (),
    ),
    "buttonSendText": style(~fontSize=14., ~color="#2096F3", ()),
    "errorText": style(
      ~position=#absolute,
      ~bottom=-4.->dp,
      ~paddingVertical=2.->dp,
      ~paddingHorizontal=13.->dp,
      ~fontSize=10.,
      ~color="#e07676",
      (),
    ),
  })
}

type comment = {
  author: int,
  email: string,
  name: string,
  url: string,
  content: string,
  editMeta: bool,
}

let newComment = (): comment => {
  /* todo read user id from local _ */
  author: 0,
  name: User.getName(),
  email: User.getEmail(),
  url: User.getUrl(),
  content: "",
  editMeta: false /* String.length(name) == 0 || String.length(email) == 0, */,
}

type errors = {
  message: string,
  email: option<string>,
}

type computedErrors = {
  name: option<string>,
  email: option<string>,
  content: option<string>,
}

let noErrors = {name: None, email: None, content: None}

type action =
  | RenderForm
  | CommentEdit(comment)
  | CommentSend(comment)
  | CommentSuccess((comment, WPRest.comment))
  | CommentError((comment, errors))

type commentState =
  | New
  | InProgress(comment)
  | Sent((comment, Js.Json.t))
  | Posted((comment, WPRest.comment))
  | Errored((comment, errors))

type animatedState = {
  metaPreviewOpacity: Animated.Value.t,
  metaPreviewY: Animated.Value.t,
  metaTextInputOpacity: Animated.Value.t,
  metaTextInputY: Animated.Value.t,
}

type state = {
  comment: commentState,
  animated: animatedState,
  renderForm: bool,
}

let sendComment = (commentToSend, success, failure) => {
  open Js.Promise
  Fetch.fetchWithInit(
    Consts.backendUrl ++ "/wp-json/wp/v2/comments",
    Fetch.RequestInit.make(
      ~method_=Post,
      ~body=Fetch.BodyInit.make(Js.Json.stringify(commentToSend)),
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      (),
    ),
  )
  |> then_(response =>
    all2((resolve(Fetch.Response.status(response)), Fetch.Response.json(response)))
  )
  |> then_(((status, json)) =>
    if status == 201 {
      WPRest.decodeComment(json)->success->resolve
    } else {
      json
      ->Obj.magic
      ->(json => {
        open Json.Decode
        {
          email: json |> optional(at(list{"data", "params", "author_email"}, string)),
          message: json |> field("message", string),
        }
      })
      ->failure
      ->resolve
    }
  )
  |> catch(err => {
    Js.log(err)
    failure({message: "Oups, une erreur est survenue!", email: None}) |> resolve
  })
}

@react.component
let make = (~databaseId, ~parentCommentId, ()) =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,
    initialState: () => {
      comment: New,
      animated: {
        metaPreviewOpacity: Animated.Value.create(transparent),
        metaPreviewY: Animated.Value.create(yHidden),
        metaTextInputOpacity: Animated.Value.create(transparent),
        metaTextInputY: Animated.Value.create(-.yHidden),
      },
      renderForm: false,
    },
    reducer: (action, state) =>
      switch action {
      | RenderForm => ReactCompat.Update({...state, renderForm: true})
      | CommentEdit(comment) =>
        switch state.comment {
        /* unless we are currently waiting for server reply for a comment
         we just allow edition of the comment, even if status is errored */
        /* | New */
        /* | InProgress(comment) */
        /* | Posted((comment, commentSuccessReponse)) */
        | Sent(_) =>
          Js.log("You can't edit while posting")
          ReactCompat.NoUpdate
        /* | Errored((comment, string)) */
        | _ => ReactCompat.Update({...state, comment: InProgress(comment)})
        }
      | CommentSend(comment) =>
        switch state.comment {
        | New =>
          ReactCompat.Update({
            ...state,
            comment: Errored((comment, {message: j`Vous n'avez encore rien écrit`, email: None})),
          })
        /* | InProgress(comment) */
        | Sent(_) =>
          Js.log("You can't post while posting already")
          ReactCompat.NoUpdate
        | Posted(_) =>
          /* impossible state as you cannot have access to CommentSend while state is Posted */
          ReactCompat.NoUpdate
        | Errored((_, _)) => ReactCompat.NoUpdate
        | _ =>
          /*
           // https://developer.wordpress.org/rest-api/reference/comments/#arguments
           // todo see how to validate this payload type, with commentToSend or similar
 */
          let pl = Js.Dict.empty()
          /* to avoid rest_comment_author_invalid */
          if comment.author > 0 {
            Js.Dict.set(pl, "author", Js.Json.number(float_of_int(comment.author)))
          }
          Js.Dict.set(pl, "author_email", Js.Json.string(comment.email))
          Js.Dict.set(pl, "author_name", Js.Json.string(comment.name))
          Js.Dict.set(pl, "author_url", Js.Json.string(comment.url))
          Js.Dict.set(pl, "author_user_agent", Js.Json.string(%raw("navigator.userAgent")))
          Js.Dict.set(pl, "content", Js.Json.string(comment.content))
          /* wordpress doesnt' store date as complete ISO, so we have to sent GMT+1 and GMT (according to site TZ - which is GMT+1) */
          Js.Dict.set(
            pl,
            "date",
            (Js.Date.now() +. 1000. *. 60. *. 60.)
            ->Js.Date.fromFloat
            ->Js.Date.toISOString
            ->String.sub(0, 19)
            ->Js.Json.string,
          )
          Js.Dict.set(
            pl,
            "date_gmt",
            Js.Date.now()
            ->Js.Date.fromFloat
            ->Js.Date.toISOString
            ->String.sub(0, 19)
            ->Js.Json.string,
          )
          Js.Dict.set(pl, "parent", Js.Json.number(float_of_int(parentCommentId)))
          Js.Dict.set(pl, "post", Js.Json.number(float_of_int(databaseId)))
          let payload = Js.Json.object_(pl)
          ReactCompat.UpdateWithSideEffects(
            {...state, comment: Sent((comment, payload))},
            ({send}) =>
              sendComment(
                payload,
                response => send(CommentSuccess((comment, response))),
                error => send(CommentError((comment, error))),
              ) |> ignore,
          )
        }
      | CommentSuccess((comment, response)) =>
        ReactCompat.Update({...state, comment: Posted((comment, response))})
      | CommentError((comment, err)) =>
        ReactCompat.Update({...state, comment: Errored((comment, err))})
      },
    didMount: ({send}) => {
      send(RenderForm)
    },
    didUpdate: ({oldSelf, newSelf}) => {
      let (animate, showPreview) = switch (oldSelf.state.comment, newSelf.state.comment) {
      | (New, InProgress(newComment)) => (
          true,
          String.length(newComment.name) > 0 && String.length(newComment.email) > 0,
        )
      | (New, Errored((newComment, _))) => (
          true,
          String.length(newComment.name) > 0 && String.length(newComment.email) > 0,
        )
      | (InProgress(oldComment), InProgress(newComment))
        if oldComment.editMeta != newComment.editMeta => (true, !newComment.editMeta)
      | (Errored(_), InProgress(newComment)) if newComment.editMeta => (true, !newComment.editMeta)
      | _ => (false, false)
      }
      if animate {
        animateFormMeta(
          ~showPreview,
          ~previewOpacity=newSelf.state.animated.metaPreviewOpacity,
          ~previewY=newSelf.state.animated.metaPreviewY,
          ~textInputOpacity=newSelf.state.animated.metaTextInputOpacity,
          ~textInputY=newSelf.state.animated.metaTextInputY,
        )
      }
    },
    render: ({state, send}) => {
      let errors = switch state.comment {
      | New => noErrors
      | InProgress(_) => noErrors
      | Sent((_, _)) => noErrors
      | Posted((_, _)) => noErrors
      | Errored((comment, errors)) =>
        let email = String.length(comment.email) == 0 ? Some("Requis") : errors.email
        let name = String.length(comment.name) == 0 ? Some("Requis") : None
        let content = switch (name, email) {
        | (None, None) if String.length(comment.content) == 0 =>
          Some(j`Vous n'avez encore rien écrit`)
        | (None, None) => Some(errors.message)
        | _ if String.length(comment.content) == 0 => Some(j`Vous n'avez encore rien écrit`)
        | _ => None
        }
        {email: email, name: name, content: content}
      }
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
      }

      let comment = switch state.comment {
      | New => newComment()
      | InProgress(comment) => comment
      | Sent((comment, _)) => comment
      | Posted((_, _)) => newComment()
      | Errored((comment, _)) => comment
      }
      /* let disabled =
         switch (state) {
         | Sent((_, _)) => true
         | _ => false
         }; */
      <View>
        <noscript>
          <Text>
            {j`🚨 Veuillez `->React.string}
            <a target="_blank" href="https://www.enable-javascript.com/fr/">
              {j`activer JavaScript`->React.string}
            </a>
            {j` pour poster un commentaire.`->React.string}
          </Text>
          <Spacer />
        </noscript>
        {!state.renderForm
          ? React.null
          : <>
              {switch state.comment {
              | Sent((_, _)) => <>
                  <ActivityIndicator size=ActivityIndicator.Size.small /> <Spacer />
                </>
              | Posted((_, _)) => <>
                  <Text> {j`👍 Commentaire envoyé!`->React.string} </Text> <Spacer />
                </>
              | _ => React.null
              }}
              <View style={styles["row"]} key=comment.name>
                {parentCommentId > 0 ? <Spacer size=XL /> : React.null}
                <View style={styles["container"]}>
                  <View style={styles["row"]}>
                    <View style={styles["avatar"]}>
                      <Spacer />
                      <Spacer size=XXS />
                      <Avatar
                        name=comment.name
                        url={"https://secure.gravatar.com/avatar/" ++
                        (Md5.make(comment.email) ++
                        "?s=96&d=mm&r=g&d=blank")}
                      />
                    </View>
                    <Spacer size=XS />
                    <View style={styles["commentBox"]}>
                      <Animated.View
                        style={
                          open Style
                          array([
                            styles["metaPreview"],
                            style(
                              ~opacity=state.animated.metaPreviewOpacity->Animated.StyleProp.float,
                              ~transform=[
                                translateY(
                                  ~translateY=state.animated.metaPreviewY->Animated.StyleProp.float,
                                ),
                              ],
                              (),
                            ),
                          ])
                        }>
                        <View style={styles["row"]}>
                          <Spacer size=S />
                          {String.length(comment.url) > 0
                            ? <ViewLink href=comment.url>
                                <Text style={styles["metaPreviewName"]}>
                                  {comment.name->React.string}
                                </Text>
                              </ViewLink>
                            : <Text style={styles["metaPreviewName"]}>
                                {comment.name->React.string}
                              </Text>}
                          <TouchableOpacity
                            onPress={_ => send(CommentEdit({...comment, editMeta: true}))}>
                            <Text style={styles["metaPreviewEdit"]}>
                              {j`  ·  `->React.string} {j`Modifier`->React.string}
                            </Text>
                          </TouchableOpacity>
                        </View>
                        <Spacer size=XXS />
                      </Animated.View>
                      <View
                        style={
                          open Style
                          array([styles["textInputCommentRow"], styles["textInputWrapper"]])
                        }>
                        <TextInputAutoMultilines
                          style={
                            open Style
                            arrayOption([
                              Some(styles["textInput"]),
                              errors.content->Option.map(_ => styles["textInputError"]),
                              Some(styles["textInputComment"]),
                            ])
                          }
                          value=comment.content
                          placeholder={"Ajouter un commentaire " ++
                          ((
                            !comment.editMeta && String.length(comment.name) > 0
                              ? "en tant que " ++ comment.name
                              : ""
                          ) ++
                          "...")}
                          onChangeText={text =>
                            send(
                              CommentEdit({
                                ...comment,
                                content: text,
                                editMeta: String.length(comment.name) == 0 ||
                                  String.length(comment.email) == 0,
                              }),
                            )}
                          onFocus={_ => {
                            let shouldEditComment = switch state.comment {
                            | New => true
                            | InProgress(_) => false
                            | Sent((_, _)) => false
                            | Posted((_, _)) => false
                            | Errored((_, _)) => false
                            }
                            if shouldEditComment {
                              send(
                                CommentEdit({
                                  ...comment,
                                  editMeta: String.length(comment.name) == 0 ||
                                    String.length(comment.email) == 0,
                                }),
                              )
                            } |> ignore
                          }}
                        />
                        {switch errors.content {
                        | Some(message) =>
                          <Text style={styles["errorText"]}> {message->React.string} </Text>
                        | None => React.null
                        }}
                      </View>
                      <Spacer size=XXS />
                      <Animated.View
                        style={
                          open Style
                          array([
                            styles["textInputs"],
                            style(
                              ~opacity=state.animated.metaTextInputOpacity->Animated.StyleProp.float,
                              ~transform=[
                                translateY(
                                  ~translateY=state.animated.metaTextInputY->Animated.StyleProp.float,
                                ),
                              ],
                              (),
                            ),
                          ])
                        }>
                        <View style={styles["row"]}>
                          <View style={styles["textInputWrapper"]}>
                            <TextInput
                              style={
                                open Style
                                arrayOption([
                                  Some(styles["textInput"]),
                                  errors.name->Option.map(_ => styles["textInputError"]),
                                  Some(styles["textInputName"]),
                                ])
                              }
                              value=comment.name
                              placeholder="Nom *"
                              onChangeText={text => {
                                User.setName(text)
                                send(CommentEdit({...comment, name: text}))
                              }}
                            />
                            {switch errors.name {
                            | Some(message) =>
                              <Text style={styles["errorText"]}> {message->React.string} </Text>
                            | None => React.null
                            }}
                          </View>
                          <Spacer size=XXS />
                          <View style={styles["textInputWrapper"]}>
                            <TextInput
                              style={
                                open Style
                                arrayOption([
                                  Some(styles["textInput"]),
                                  errors.email->Option.map(_ => styles["textInputError"]),
                                  Some(styles["textInputEmail"]),
                                ])
                              }
                              value=comment.email
                              placeholder="Email *"
                              onChangeText={text => {
                                User.setEmail(text)
                                send(CommentEdit({...comment, email: text}))
                              }}
                            />
                            {switch errors.email {
                            | Some(message) =>
                              <Text style={styles["errorText"]}> {message->React.string} </Text>
                            | None => React.null
                            }}
                          </View>
                          <Spacer size=XXS />
                          <View style={styles["textInputWrapper"]}>
                            <TextInput
                              style={
                                open Style
                                array([styles["textInput"], styles["textInputUrl"]])
                              }
                              value=comment.url
                              placeholder="https://site.web"
                              onChangeText={text => {
                                User.setUrl(text)
                                send(CommentEdit({...comment, url: text}))
                              }}
                            />
                          </View>
                        </View>
                      </Animated.View>
                      <TouchableOpacity
                        onPress={_ => send(CommentSend(comment))} style={styles["buttonSend"]}>
                        <Text style={styles["buttonSendText"]}> {"Envoyer"->React.string} </Text>
                      </TouchableOpacity>
                    </View>
                  </View>
                </View>
              </View>
            </>}
      </View>
    },
  })
