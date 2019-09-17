open BsReactNative;

let styles = Style.(StyleSheet.create({"separator": style([])}));

let makeAsString = category => {
  "<span style=\"display: flex; flex-direction: row; justify-content: center; align-items: center; margin: 60px auto; width: 80%;\">"
  ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
  ++ (
    switch (category) {
    | `permaculture => "<img src=\"/images/separator-feather.png\" style=\"margin: 0 10px; width: 36.5px; height: 11.5px;\" alt=\"\" />"
    | `alimentation
    | `default => "<img src=\"/images/separator-flower.png\" style=\"margin: 0 10px; width: 62.5px; height: 13px;\" alt=\"\" />"
    | `bienEtre
    | `lifestyle => "<img src=\"/images/separator-hearts.png\" style=\"margin: 0 10px; width: 48px; height: 15px;\" alt=\"\" />"
    }
  )
  ++ "<span style=\"flex: 1; height: 1px; background: #A6A6A7;\"></span>"
  ++ "</span>";
};

[@react.component]
let make = () => {
  <View style=styles##separator />;
};
