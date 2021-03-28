// open Belt;
// open ReactNative;
// let defaultSize = 14.;
// let defaultColor = Consts.Colors.grey;
// let styles =
//   Style.(
//     StyleSheet.create({"touchable": style(~justifyContent=`center, ())})
//   );
// module Login = [%graphql
//   {|
//   mutation LoginUser($username: String!, $password: String!) {
//     login( input: {
//       clientMutationId: "userLogin"
//       username: $username
//       password: $password
//     } ) {
//       authToken
//       refreshToken
//       user {
//         id
//         name
//         email
//         url
//       }
//     }
//   }
// |}
// ];
// module LoginMutation = ReasonApollo.CreateMutation(Login);
// [@react.component]
// let make = () => {
//   let (showLoginForm, setShowLoginForm) = React.useState(() => false);
//   let (username, setUsername) = React.useState(() => None);
//   let (pwd, setPwd) = React.useState(() => None);
//   let isLogged = Auth.isLogged();
//   <LoginMutation>
//     ...{(login, _res) =>
//       <>
//         {showLoginForm
//            ? <SpacedView
//                style=Style.(
//                  style(
//                    ~backgroundColor="#fff",
//                    ~width=300.->dp,
//                    ~alignSelf=`center,
//                    (),
//                  )
//                )>
//                <Text> "Login"->React.string </Text>
//                <Spacer size=XS />
//                <TextInput
//                  style=Style.(
//                    style(
//                      ~color="#333",
//                      ~borderWidth=1.,
//                      ~borderColor="#333",
//                      ~padding=(Spacer.space /. 2.)->dp,
//                      ~borderRadius=Consts.Radius.field,
//                      (),
//                    )
//                  )
//                  value={username->Option.getWithDefault("")}
//                  onChangeText={text => setUsername(_ => Some(text))}
//                  autoCapitalize=`none
//                  autoCorrect=false
//                  // autoCompleteType=`email
//                  autoFocus=true
//                  clearButtonMode=`always
//                  keyboardType=`emailAddress
//                  placeholder="Nom utilisateur"
//                  textContentType=`emailAddress
//                />
//                <Spacer />
//                <Text> "Password"->React.string </Text>
//                <TextInput
//                  style=Style.(
//                    style(
//                      ~color="#333",
//                      ~borderWidth=1.,
//                      ~borderColor="#333",
//                      ~padding=(Spacer.space /. 2.)->dp,
//                      ~borderRadius=Consts.Radius.field,
//                      (),
//                    )
//                  )
//                  defaultValue={pwd->Option.getWithDefault("")}
//                  onChangeText={text => setPwd(_ => Some(text))}
//                  secureTextEntry=true
//                  placeholder="mot de passe"
//                />
//                <Spacer />
//                <TouchableOpacity
//                  style=Style.(
//                    viewStyle(
//                      ~backgroundColor="#333",
//                      ~padding=(Spacer.space /. 2.)->dp,
//                      ~borderRadius=Consts.Radius.field,
//                      (),
//                    )
//                  )
//                  onPress={_ => {
//                    let loginMutation =
//                      Login.make(
//                        ~username=username->Option.getWithDefault(""),
//                        ~password=pwd->Option.getWithDefault(""),
//                        (),
//                      );
//                    login(~variables=loginMutation##variables, ())
//                    ->FutureJs.fromPromise(Js.String.make)
//                    ->Future.tap(
//                        fun
//                        | Ok(response) => {
//                            switch (response) {
//                            | Data(data) =>
//                              data##login
//                              ->Option.map(loginData => {
//                                  Auth.login(loginData);
//                                  setShowLoginForm(_ => false);
//                                })
//                              ->ignore
//                            | _ => ()
//                            };
//                          }
//                        | _ => (),
//                      )
//                    ->ignore;
//                  }}>
//                  <Text style=Style.(textStyle(~color="#eee", ()))>
//                    "Login"->React.string
//                  </Text>
//                </TouchableOpacity>
//              </SpacedView>
//            : React.null}
//         {isLogged
//            ? <TouchableOpacity
//                style=styles##touchable
//                onPress={_ => {
//                  Auth.logout();
//                  setUsername(_ => None);
//                  setPwd(_ => None);
//                }}>
//                <Text> {j|☆|j}->React.string </Text>
//              </TouchableOpacity>
//            : <TouchableOpacity
//                style=styles##touchable
//                onPress={_ => setShowLoginForm(_ => true)}>
//                <Text> {j|⭑|j}->React.string </Text>
//              </TouchableOpacity>}
//       </>
//     }
//   </LoginMutation>;
// };
