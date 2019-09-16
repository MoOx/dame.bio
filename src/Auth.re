open Belt;
open Storage;

let isLogged = (): bool => store->authTokenGet->Option.isSome;

let login = loginData => {
  Js.log2("login data", loginData);
  store->authTokenSet(loginData##authToken);
  store->refreshTokenSet(loginData##refreshToken);
  loginData##user
  ->Option.map(user => {
      user##name->Option.map(store->nameSet)->ignore;
      user##email->Option.map(store->emailSet)->ignore;
      user##url->Option.map(store->urlSet)->ignore;
    })
  ->ignore;
  saveStore();
};

let logout = () => {
  cleanStore();
  saveStore();
};
