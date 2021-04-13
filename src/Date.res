type relativeFormat

@new @module
external createRelativeFormat: string => relativeFormat = "intl-relativeformat"

/* https://github.com/yahoo/intl-relativeformat/issues/34 */
%%raw(`(typeof window !== "undefined" ? window : global).IntlRelativeFormat = IntlRelativeformat`)

%%raw(`require('intl-relativeformat/dist/locale-data/fr.js')`)

let relativeFormat = createRelativeFormat("fr")

let relativeDateFromString: string => string = %raw(
  "function(s) {return relativeFormat.format(new Date(s))}"
)

let relativeDate: Js.Date.t => string = %raw(
  "function(s) {return relativeFormat.format(new Date(s))}"
)
