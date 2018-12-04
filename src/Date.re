type relativeFormat;

[@bs.new] [@bs.module]
external createRelativeFormat: string => relativeFormat =
  "intl-relativeformat";

/* https://github.com/yahoo/intl-relativeformat/issues/34 */
%raw
{|(typeof window !== "undefined" ? window : global).IntlRelativeFormat = IntlRelativeformat|};

%raw
{|require('intl-relativeformat/dist/locale-data/fr.js')|};

let relativeFormat = createRelativeFormat("fr");

let relativeDate: string => string = [%raw
  "function(s) {return relativeFormat.format(new Date(s))}"
];
