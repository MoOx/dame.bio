type initialOptions = {
  .
  // "getAllPos": option(bool),
  "canRestoreInitialState": bool,
};

[@bs.module "./withApolloClient"]
external make: (~component: 'a, ~initialOptions: initialOptions) => 'a =
  "default";
