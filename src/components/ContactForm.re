open Belt;
open BsReactNative;

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
      "page": style([maxWidth(Pt(400.))]),
      "messageBox":
        style([
          maxWidth(Pt(400.)),
          paddingVertical(Pt(Spacer.space)),
          paddingHorizontal(Pt(Spacer.space *. 1.5)),
        ]),
      "textInputs": style([]),
      "textInputWrapper": style([paddingBottom(Pt(10.))]),
      "textInput":
        style([
          color(String("#49443A")),
          backgroundColor(String("#fff")),
          /* Don't go lower than 16 to avoid Safari iOS to zoom on the page */
          fontSize(Float(16.)),
          lineHeight(16.),
          margin(Pt(0.)),
          paddingVertical(Pt(10.)),
          paddingHorizontal(Pt(12.)),
          borderWidth(1.),
          borderColor(String("#ddd")),
        ]),
      "textInputError": style([borderColor(String("#e07676"))]),
      "textInputName": style([borderRadius(16.)]),
      "textInputEmail": style([borderRadius(16.)]),
      "textInputMessage":
        style([
          paddingLeft(Pt(12.)),
          paddingRight(Pt(80.)),
          borderRadius(16.),
        ]),
      "buttonSend": style([fontWeight(`_600), padding(Pt(10.))]),
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

type message = {
  email: string,
  name: string,
  content: string,
};

let newMessage = (): message => {
  {name: User.getName(), email: User.getEmail(), content: ""};
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
  | MessageEdit(message)
  | MessageSend(message)
  | MessageSuccess((message, Js.Json.t))
  | MessageError((message, errors));

type messageState =
  | New
  | InProgress(message)
  | Sent((message, string))
  | Posted(message)
  | Errored((message, errors));

type state = {message: messageState};

let sendMessage = (messageToSend, success, failure) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      "/",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~headers=
          Fetch.HeadersInit.make({
            "Content-Type": "application/x-www-form-urlencoded",
          }),
        ~body=Fetch.BodyInit.make(messageToSend),
        (),
      ),
    )
    |> then_(response =>
         all2((
           resolve(Fetch.Response.status(response)),
           Fetch.Response.json(response),
         ))
       )
    |> then_(((status, json)) => {
         Js.log3("response", status, json);
         json->Obj.magic->success->resolve;
         //  if (status == 201) {
         //    json->Obj.magic->success->resolve;
         //  } else {
         //    {message: "Oups, une erreur est survenue!", email: None}
         //    ->failure
         //    ->resolve;
         //  }
       })
    |> catch(err => {
         Js.log(err);
         failure({message: "Oups, une erreur est survenue!", email: None})
         |> resolve;
       })
  );

let formName = "contact";

let component = ReasonReact.reducerComponent("ContactForm");

let make = (~page=?, _children) => {
  ...component,
  initialState: () => {message: New},
  reducer: (action, state) =>
    switch (action) {
    | MessageEdit(message) =>
      switch (state.message) {
      /* unless we are currently waiting for server reply for a message
         we just allow edition of the message, even if status is errored */
      /* | New */
      /* | InProgress(message) */
      /* | Posted((message, messageSuccessReponse)) */
      | Sent(_) =>
        Js.log("You can't edit while posting");
        ReasonReact.NoUpdate;
      /* | Errored((message, string)) */
      | _ => ReasonReact.Update({message: InProgress(message)})
      }
    | MessageSend(message) =>
      switch (state.message) {
      | New =>
        ReasonReact.Update({
          message:
            Errored((
              message,
              {message: {j|Vous n'avez encore rien écrit|j}, email: None},
            )),
        })
      /* | InProgress(message) */
      | Sent(_) =>
        Js.log("You can't post while posting already");
        ReasonReact.NoUpdate;
      | Posted(_) =>
        /* impossible state as you cannot have access to MessageSend while state is Posted */
        ReasonReact.NoUpdate
      | Errored((_, _)) => ReasonReact.NoUpdate
      | _ =>
        let payload =
          Utils.(
            "form-name"
            ++ "="
            ++ encodeURI(formName)
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
        ReasonReact.UpdateWithSideEffects(
          {message: Sent((message, payload))},
          ({send}) =>
            sendMessage(
              payload,
              response => send(MessageSuccess((message, response))),
              error => send(MessageError((message, error))),
            )
            |> ignore,
        );
      }
    | MessageSuccess((message, _response)) =>
      ReasonReact.Update({message: Posted(message)})
    | MessageError((message, err)) =>
      ReasonReact.Update({message: Errored((message, err))})
    },
  render: ({state, send}) => {
    let errors =
      switch (state.message) {
      | New => noErrors
      | InProgress(_) => noErrors
      | Sent((_, _)) => noErrors
      | Posted(_) => noErrors
      | Errored((message, errors)) =>
        let email =
          String.length(message.email) == 0 ? Some("Requis") : errors.email;
        let name = String.length(message.name) == 0 ? Some("Requis") : None;
        let content =
          switch (name, email) {
          | (None, None) when String.length(message.content) == 0 =>
            Some({j|Vous n'avez encore rien écrit|j})
          | (None, None) => Some(errors.message)
          | _ when String.length(message.content) == 0 =>
            Some({j|Vous n'avez encore rien écrit|j})
          | _ => None
          };
        {email, name, content};
      };

    let message =
      switch (state.message) {
      | New => newMessage()
      | InProgress(message) => message
      | Sent((message, _)) => message
      | Posted(_) => newMessage()
      | Errored((message, _)) => message
      };
    <View>
      <Heading> {j|Contact|j}->ReasonReact.string </Heading>
      <Spacer />
      {switch (state.message) {
       | Sent((_, _)) => <> <ActivityIndicator size=`small /> <Spacer /> </>
       | Posted(_) =>
         <>
           <Text> {j|👍 Message envoyé!|j}->ReasonReact.string </Text>
           <Spacer />
         </>
       | _ => ReasonReact.null
       }}
      {ReactDOMRe.createElementVariadic(
         "form",
         ~props=
           ReactDOMRe.objToDOMProps({
             "name": formName,
             "method": "post",
             "data-netlify": "true",
             "data-netlify-honeypot": "subject",
           }),
         [|
           <View style=styles##row>
             {page
              ->Option.map(item =>
                  <SpacedView style=styles##page>
                    <Html content=item##content />
                  </SpacedView>
                )
              ->Option.getWithDefault(ReasonReact.null)}
             <View>
               <noscript>
                 <Text>
                   {j|🚨 Veuillez |j}->ReasonReact.string
                   <a
                     target="_blank"
                     href="https://www.qwant.com/?q=message%20activer%20javascript">
                     {j|activer JavaScript|j}->ReasonReact.string
                   </a>
                   {j| pour envoyer un message.|j}->ReasonReact.string
                 </Text>
                 <Spacer />
               </noscript>
               <ImageBackgroundFromUri
                 style=styles##messageBox
                 resizeMode=`stretch
                 uri="/images/watercolor-square-pink.png">
                 <Spacer />
                 // <input> to make netlify bots happy
                 <input type_="hidden" name="form-name" value="contact" />
                 <div style={ReactDOMRe.Style.make(~display="none", ())}>
                   <input type_="text" name="name" value="" />
                   <input type_="email" name="email" value="" />
                   <input type_="text" name="content" value="" />
                   // data-netlify-honeypot
                   <input type_="text" name="subject" value="" />
                 </div>
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
                     value={message.name}
                     placeholder="Nom *"
                     onChangeText={text => {
                       User.setName(text);
                       send(MessageEdit({...message, name: text}));
                     }}
                   />
                   {switch (errors.name) {
                    | Some(message) =>
                      <Text style=styles##errorText>
                        message->ReasonReact.string
                      </Text>
                    | None => ReasonReact.null
                    }}
                 </View>
                 <Spacer />
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
                     value={message.email}
                     placeholder="Email *"
                     onChangeText={text => {
                       User.setEmail(text);
                       send(MessageEdit({...message, email: text}));
                     }}
                   />
                   {switch (errors.email) {
                    | Some(message) =>
                      <Text style=styles##errorText>
                        message->ReasonReact.string
                      </Text>
                    | None => ReasonReact.null
                    }}
                 </View>
                 <Spacer size=S />
                 <View style={Style.concat([styles##textInputWrapper])}>
                   <TextInput
                     style=Style.(
                       concat([
                         styles##textInput,
                         switch (errors.content) {
                         | Some(_) => styles##textInputError
                         | None => style([])
                         },
                         styles##textInputMessage,
                       ])
                     )
                     value={message.content}
                     placeholder={j|Votre message…|j}
                     onChangeText={text =>
                       send(MessageEdit({...message, content: text}))
                     }
                     multiline=true
                     numberOfLines=8
                   />
                   {switch (errors.content) {
                    | Some(message) =>
                      <Text style=styles##errorText>
                        message->ReasonReact.string
                      </Text>
                    | None => ReasonReact.null
                    }}
                 </View>
                 <Spacer size=XXS />
                 <TouchableOpacity
                   onPress={() => send(MessageSend(message))}
                   style=styles##buttonSend>
                   <Text style=styles##buttonSendText>
                     {j|Envoyer|j}->ReasonReact.string
                   </Text>
                 </TouchableOpacity>
               </ImageBackgroundFromUri>
             </View>
           </View>,
         |],
       )}
    </View>;
  },
};
