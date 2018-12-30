[@bs.module "../../../../src/components/BodyAsScrollView"]
external reactClass: ReasonReact.reactClass = "default";

type keyboardDismissMode =
  | None
  | Interactive
  | OnDrag;

let make = (~keyboardDismissMode=None, children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={
      "keyboardDismissMode":
        switch (keyboardDismissMode) {
        | None => "none"
        | Interactive => "interactive"
        | OnDrag => "on-drag"
        },
    },
    children,
  );
};
