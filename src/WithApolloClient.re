[@bs.module "./withApolloClient"]
external withApolloClient: 'a => 'a = "default";

let make = withApolloClient;
