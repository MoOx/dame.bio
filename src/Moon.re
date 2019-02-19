let daysPerMoon = 29.5305882;
let daysPerYear = 365.25;
let daysPerMonth = 30.6;
let nineteenHundred = 694039.09;

type phase =
  | New
  | WaxingCrescent
  | Quarter
  | WaxingGibbous
  | Full
  | WaningGibbous
  | LastQuarter
  | WaningCrescent;

type moonPhase = {
  unicode: string,
  phase,
};

let moonPhases = [|
  {unicode: {js|🌑|js}, phase: New},
  {unicode: {js|🌒|js}, phase: WaxingCrescent},
  {unicode: {js|🌓|js}, phase: Quarter},
  {unicode: {js|🌔|js}, phase: WaxingGibbous},
  {unicode: {js|🌕|js}, phase: Full},
  {unicode: {js|🌖|js}, phase: WaningGibbous},
  {unicode: {js|🌗|js}, phase: LastQuarter},
  {unicode: {js|🌘|js}, phase: WaningCrescent},
|];

let phaseFromDate = date => {
  let tmpMonth = date->Js.Date.getMonth +. 1.;
  let year = date->Js.Date.getFullYear +. (tmpMonth < 3. ? (-1.) : 0.);
  let month = tmpMonth < 3. ? tmpMonth +. 12. : tmpMonth;
  let day = date->Js.Date.getDate;

  let totalDaysElapsed =
    year *. daysPerYear +. month *. daysPerMonth +. day -. nineteenHundred;
  let totalDaysElapsedSinceLastMoon = totalDaysElapsed /. daysPerMoon;
  // subtract integer part to leave fractional part of original
  let daysElapsed =
    totalDaysElapsedSinceLastMoon
    -. totalDaysElapsedSinceLastMoon->int_of_float->float_of_int;

  let phase =
    Js.Math.round(daysElapsed *. moonPhases->Array.length->float_of_int);
  // turn 8 into 0
  let moonIndex =
    int_of_float(
      phase >= moonPhases->Array.length->float_of_int ? 0. : phase,
    );
  moonPhases->Array.get(moonIndex);
};

let currentPhase = () => phaseFromDate(Js.Date.now()->Js.Date.fromFloat);
