open Belt
open ReactNative

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
    "page": style(~flexGrow=1., ~flexShrink=1., ~flexBasis=200.->dp, ()),
    "messageBox": style(
      ~flexGrow=1.,
      ~flexShrink=1.,
      ~paddingVertical=dp(Spacer.space),
      ~paddingHorizontal=dp(Spacer.space *. 1.5),
      (),
    ),
    "textInputs": style(),
    "textInputWrapper": style(~paddingBottom=10.->dp, ()),
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
    "textInputName": style(~borderRadius=Consts.Radius.field, ()),
    "textInputEmail": style(~borderRadius=Consts.Radius.field, ()),
    "textInputMessage": style(
      ~paddingLeft=12.->dp,
      ~paddingRight=80.->dp,
      ~borderRadius=Consts.Radius.field,
      (),
    ),
    "buttonSend": style(~fontWeight=#_600, ~padding=10.->dp, ()),
    "buttonSendText": style(~fontSize=14., ~color="#2096F3", ()),
    "errorText": style(
      ~position=#absolute,
      ~bottom=dp(-4.),
      ~paddingVertical=2.->dp,
      ~paddingHorizontal=13.->dp,
      ~fontSize=10.,
      ~color="#e07676",
      (),
    ),
  })
}

type message = {
  email: string,
  name: string,
  content: string,
}

let newMessage = (): message => {
  name: User.getName(),
  email: User.getEmail(),
  content: "",
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
  | MessageEdit(message)
  | MessageSend(message)
  | MessageSuccess(message)
  | MessageError((message, errors))

type messageState =
  | New
  | InProgress(message)
  // netlify
  // | Sent((message, string))
  | Sent((message, {"accessKey": string, "name": string, "email": string, "message": string}))
  | Posted(message)
  | Errored((message, errors))

type state = {message: messageState}

let staticFormsAccessKey = "45eae26b-de71-4e38-9d09-00126bb4e0a5" // contact2019@

let sendMessage = (messageToSend, success, failure) => {
  open Js.Promise
  Fetch.fetchWithInit(
    // netlify
    // "/",
    // staticforms
    "https://api.staticforms.xyz/submit",
    Fetch.RequestInit.make(
      ~method_=Post,
      ~headers=Fetch.HeadersInit.make({
        // netlify
        // "Content-Type": "application/x-www-form-urlencoded",
        // staticforms
        "Content-Type": "application/json",
      }),
      // netlify
      // ~body=Fetch.BodyInit.make(messageToSend),

      ~body=Fetch.BodyInit.make(Js.Json.stringifyAny(messageToSend)->Option.getWithDefault("")),
      (),
    ),
  )
  |> then_(response => response->Fetch.Response.status->resolve)
  |> then_(status => {
    Js.log2("response", status)
    if status == 200 {
      status->success->resolve
    } else {
      {message: "Votre message n'a pas pu être envoyé", email: None}->failure->resolve
    }
  })
  |> catch(err => {
    Js.log(err)
    failure({message: "Oups, une erreur est survenue!", email: None}) |> resolve
  })
}

let formName = "contact"

@react.component
let make = (~page: option<WPGraphQL.GetPage.GetPage_inner.t_pages_nodes>=?, ()) =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,
    initialState: () => {message: New},
    reducer: (action, state) =>
      switch action {
      | MessageEdit(message) =>
        switch state.message {
        /* unless we are currently waiting for server reply for a message
         we just allow edition of the message, even if status is errored */
        /* | New */
        /* | InProgress(message) */
        /* | Posted((message, messageSuccessReponse)) */
        | Sent(_) =>
          Js.log("You can't edit while posting")
          ReactCompat.NoUpdate
        /* | Errored((message, string)) */
        | _ => ReactCompat.Update({message: InProgress(message)})
        }
      | MessageSend(message) =>
        switch state.message {
        | New =>
          ReactCompat.Update({
            message: Errored((message, {message: j`Vous n'avez encore rien écrit`, email: None})),
          })
        /* | InProgress(message) */
        | Sent(_) =>
          Js.log("You can't post while posting already")
          ReactCompat.NoUpdate
        | Posted(_) =>
          /* impossible state as you cannot have access to MessageSend while state is Posted */
          ReactCompat.NoUpdate
        | Errored((_, _)) => ReactCompat.NoUpdate
        | _ =>
          /*
           let payload =
             Utils.(
               "form-name"
               ++ "="
               ++ encodeURI(formName)
               ++ "&"
               ++ "name"
               ++ "="
               ++ encodeURI(message.name)
               ++ "&"
               ++ "email"
               ++ "="
               ++ encodeURI(message.email)
               ++ "&"
               ++ "content"
               ++ "="
               ++ encodeURI(message.content)
             );
 */
          let payload = {
            "accessKey": staticFormsAccessKey,
            "name": message.name,
            "email": message.email,
            "message": message.content,
          }
          ReactCompat.UpdateWithSideEffects(
            {message: Sent((message, payload))},
            ({send}) =>
              sendMessage(
                payload,
                _status => send(MessageSuccess(message)),
                error => send(MessageError((message, error))),
              ) |> ignore,
          )
        // netlify
        }
      | MessageSuccess(message) => ReactCompat.Update({message: Posted(message)})
      | MessageError((message, err)) => ReactCompat.Update({message: Errored((message, err))})
      },
    render: ({state, send}) => {
      let errors = switch state.message {
      | New => noErrors
      | InProgress(_) => noErrors
      | Sent((_, _)) => noErrors
      | Posted(_) => noErrors
      | Errored((message, errors)) =>
        let email = String.length(message.email) == 0 ? Some("Requis") : errors.email
        let name = String.length(message.name) == 0 ? Some("Requis") : None
        let content = switch (name, email) {
        | (None, None) if String.length(message.content) == 0 =>
          Some(j`Vous n'avez encore rien écrit`)
        | (None, None) => Some(errors.message)
        | _ if String.length(message.content) == 0 => Some(j`Vous n'avez encore rien écrit`)
        | _ => None
        }
        {email: email, name: name, content: content}
      }

      let message = switch state.message {
      | New => newMessage()
      | InProgress(message) => message
      | Sent((message, _)) => message
      | Posted(_) => newMessage()
      | Errored((message, _)) => message
      }
      <SpacedView>
        <Heading> {j`Contact`->React.string} </Heading>
        <Spacer />
        /*
          // <form & input> to make netlify bots happy
          * /
         {ReactDOMRe.createElementVariadic(
            "form",
            ~props=
              ReactDOMRe.objToDOMProps({
                "name": formName,
                "method": "post",
                "netlify": "true",
                "netlify-honeypot": "subject",
                "hidden": "true",
              }),
            [|
              <>
                <input type_="text" name="name" />
                <input type_="email" name="email" />
                <input type_="text" name="content" />
                /*
                 // data-netlify-honeypot
                 */
                <input type_="text" name="subject" />
              </>,
            |],
          )}
 */
        <View style={styles["row"]}>
          {page
          ->Option.map(item => <View style={styles["page"]}> <Html content=item.content /> </View>)
          ->Option.getWithDefault(React.null)}
          <Spacer />
          <View>
            {switch state.message {
            | Sent((_, _)) => <>
                <ActivityIndicator size=ActivityIndicator.Size.small /> <Spacer />
              </>
            | Posted(_) => <> <Text> {j`👍 Message envoyé!`->React.string} </Text> <Spacer /> </>
            | _ => React.null
            }}
            <noscript>
              <Text>
                {j`🚨 Veuillez `->React.string}
                <a target="_blank" href="https://www.qwant.com/?q=comment%20activer%20javascript">
                  {j`activer JavaScript`->React.string}
                </a>
                {j` pour envoyer un message.`->React.string}
              </Text>
              <Spacer />
            </noscript>
            <ImageBackgroundFromUri
              style={styles["messageBox"]}
              resizeMode=#stretch
              uri="/images/watercolor-square-pink.png">
              <Spacer />
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
                  value=message.name
                  placeholder="Nom *"
                  onChangeText={text => {
                    User.setName(text)
                    send(MessageEdit({...message, name: text}))
                  }}
                />
                {switch errors.name {
                | Some(message) =>
                  <Text style={styles["errorText"]}> {message->React.string} </Text>
                | None => React.null
                }}
              </View>
              <Spacer />
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
                  value=message.email
                  placeholder="Email *"
                  onChangeText={text => {
                    User.setEmail(text)
                    send(MessageEdit({...message, email: text}))
                  }}
                />
                {switch errors.email {
                | Some(message) =>
                  <Text style={styles["errorText"]}> {message->React.string} </Text>
                | None => React.null
                }}
              </View>
              <Spacer size=S />
              <View style={styles["textInputWrapper"]}>
                <TextInput
                  style={
                    open Style
                    arrayOption([
                      Some(styles["textInput"]),
                      errors.content->Option.map(_ => styles["textInputError"]),
                      Some(styles["textInputMessage"]),
                    ])
                  }
                  value=message.content
                  placeholder=j`Votre message…`
                  onChangeText={text => send(MessageEdit({...message, content: text}))}
                  multiline=true
                  numberOfLines=8
                />
                {switch errors.content {
                | Some(message) =>
                  <Text style={styles["errorText"]}> {message->React.string} </Text>
                | None => React.null
                }}
              </View>
              <Spacer size=XXS />
              <TouchableOpacity
                onPress={_ => send(MessageSend(message))} style={styles["buttonSend"]}>
                <Text style={styles["buttonSendText"]}> {j`Envoyer`->React.string} </Text>
              </TouchableOpacity>
            </ImageBackgroundFromUri>
          </View>
        </View>
      </SpacedView>
    },
  })
