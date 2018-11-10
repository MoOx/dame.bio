open BsReactNative;

open Helpers;

let apiBaseUrl = "https://dame.bio/";

let opaque = 1.;
let transparent = 0.;
let yVisible = 0.;
let yHidden = 40.;
let animatedMetaPreviewOpacity = Animated.Value.create(transparent);
let animatedMetaPreviewY = Animated.Value.create(yHidden);
let animatedMetaTextInputOpacity = Animated.Value.create(transparent);
let animatedMetaTextInputY = Animated.Value.create(-. yHidden);

let animateFormMeta = showPreview =>
  Animated.start(
    Animated.parallel(
      [|
        Animated.spring(
          ~value=animatedMetaPreviewOpacity,
          ~toValue=`raw(showPreview ? opaque : transparent),
          (),
        ),
        Animated.spring(
          ~value=animatedMetaPreviewY,
          ~toValue=`raw(showPreview ? yVisible : yHidden),
          (),
        ),
        Animated.spring(
          ~value=animatedMetaTextInputOpacity,
          ~toValue=`raw(showPreview ? transparent : opaque),
          (),
        ),
        Animated.spring(
          ~value=animatedMetaTextInputY,
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
      "row": style([flexDirection(Row)]),
      "avatar":
        style([
          /* compensate TextInput borderWidth */
          paddingVertical(Pt(2.)),
        ]),
      "commentBox": style([flex(1.)]),
      "metaPreview":
        style([
          opacity(Animated(animatedMetaPreviewOpacity)),
          Transform.makeAnimated(~translateY=animatedMetaPreviewY, ()),
        ]),
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
      "textInputs":
        style([
          opacity(Animated(animatedMetaTextInputOpacity)),
          Transform.makeAnimated(~translateY=animatedMetaTextInputY, ()),
        ]),
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
          top(Pt(30.)),
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

type state =
  | New
  | InProgress(comment)
  | Sent((comment, Js.Json.t))
  | Posted((comment, Structures.comment))
  | Errored((comment, errors));

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
  initialState: () => New,
  reducer: (action, state) =>
    switch (action) {
    | CommentEdit(comment) =>
      switch (state) {
      /* unless we are currently waiting for server reply for a comment
         we just allow edition of the comment, even if status is errored */
      /* | New */
      /* | InProgress(comment) */
      /* | Posted((comment, commentSuccessReponse)) */
      | Sent(_) =>
        Js.log("You can't edit while posting");
        ReasonReact.NoUpdate;
      /* | Errored((comment, string)) */
      | _ => ReasonReact.Update(InProgress(comment))
      }
    | CommentSend(comment) =>
      switch (state) {
      | New =>
        ReasonReact.Update(
          Errored((
            comment,
            {message: {j|Vous n'avez encore rien écrit|j}, email: None},
          )),
        )
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
          Sent((comment, payload)),
          (
            ({send}) =>
              sendComment(
                payload,
                response => send(CommentSuccess((comment, response))),
                error => send(CommentError((comment, error))),
              )
              |> ignore
          ),
        );
      }
    | CommentSuccess((comment, response)) =>
      ReasonReact.Update(Posted((comment, response)))
    | CommentError((comment, err)) =>
      ReasonReact.Update(Errored((comment, err)))
    },
  didUpdate: ({oldSelf, newSelf}) => {
    let (animate, showPreview) =
      switch (oldSelf.state, newSelf.state) {
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
      animateFormMeta(showPreview);
    };
  },

  render: ({state, send}) =>
    <View style=styles##row>
      {parentCommentId > 0 ? <Spacer size=XL /> : nothing}
      <View>
        {
          switch (state) {
          | Sent((_, _)) =>
            <> <Text> {{j|Envoi...|j} |> text} </Text> <Spacer /> </>
          | Posted((_, comment)) => <Comment comment canReply=false />
          | _ => nothing
          }
        }
        {
          let errors =
            switch (state) {
            | New => noErrors
            | InProgress(_) => noErrors
            | Sent((_, _)) => noErrors
            | Posted((_, _)) => noErrors
            | Errored((comment, errors)) =>
              Js.log2("ERRORS", errors);
              let email =
                String.length(comment.email) == 0 ?
                  Some("Requis") : errors.email;
              let name =
                String.length(comment.name) == 0 ? Some("Requis") : None;
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
          Js.log(errors);
          switch (errors.name, errors.email) {
          | (Some(_), Some(_)) => animateFormMeta(false)
          | _ => ()
          };

          let comment =
            switch (state) {
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
          <View style=styles##row>
            <View style=styles##avatar>
              <Spacer />
              <Spacer size=XXS />
              {
                let url =
                  "https://secure.gravatar.com/avatar/"
                  ++ Md5.make(comment.email)
                  ++ "?s=96&d=mm&r=g&d=blank";
                <Avatar name={comment.name} url />;
              }
            </View>
            <Spacer size=XS />
            <View style=styles##commentBox>
              <Animated.View style=styles##metaPreview>
                <View style=styles##row>
                  <Spacer size=S />
                  {
                    String.length(comment.url) > 0 ?
                      <TextLink
                        style=styles##metaPreviewName href={comment.url}>
                        {comment.name |> text}
                      </TextLink> :
                      <Text style=styles##metaPreviewName>
                        {comment.name |> text}
                      </Text>
                  }
                  <TouchableOpacity
                    onPress={
                      () =>
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
                style={
                  Style.concat([
                    styles##textInputCommentRow,
                    styles##textInputWrapper,
                  ])
                }>
                <TextInput
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
                  multiline=true
                  onChangeText={
                    text =>
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
                  onFocus={
                    () => {
                      let shouldEditComment =
                        switch (state) {
                        | New => true
                        | InProgress(_) => true
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
                    }
                  }
                />
                {
                  switch (errors.content) {
                  | Some(message) =>
                    <Text style=styles##errorText> {message |> text} </Text>
                  | None => nothing
                  }
                }
              </View>
              <Spacer size=XXS />
              <Animated.View style=styles##textInputs>
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
                      onChangeText={
                        text => {
                          localSave("name", text);
                          send(CommentEdit({...comment, name: text}));
                        }
                      }
                    />
                    {
                      switch (errors.name) {
                      | Some(message) =>
                        <Text style=styles##errorText>
                          {message |> text}
                        </Text>
                      | None => nothing
                      }
                    }
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
                      onChangeText={
                        text => {
                          localSave("email", text);
                          send(CommentEdit({...comment, email: text}));
                        }
                      }
                    />
                    {
                      switch (errors.email) {
                      | Some(message) =>
                        <Text style=styles##errorText>
                          {message |> text}
                        </Text>
                      | None => nothing
                      }
                    }
                  </View>
                  <Spacer size=XXS />
                  <View style=styles##textInputWrapper>
                    <TextInput
                      style=Style.(
                        concat([styles##textInput, styles##textInputUrl])
                      )
                      value={comment.url}
                      placeholder="https://site.web"
                      onChangeText={
                        text => {
                          localSave("url", text);
                          send(CommentEdit({...comment, url: text}));
                        }
                      }
                    />
                  </View>
                </View>
              </Animated.View>
              <TouchableOpacity
                onPress={() => send(CommentSend(comment))}
                style=styles##buttonSend>
                <Text style=styles##buttonSendText> {"Envoyer" |> text} </Text>
              </TouchableOpacity>
            </View>
          </View>;
        }
      </View>
    </View>,
};
