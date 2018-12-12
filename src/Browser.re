[@bs.val] external window: 'a = "window";

let isBrowser = () => Js.typeof(window) !== "undefined";

let isNotBrowser = () => !isBrowser();
