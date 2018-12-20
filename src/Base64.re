[@bs.module "b64-lite"] external toBase64: string => string = "toBase64";
[@bs.module "b64-lite"] external fromBase64: string => string = "fromBase64";

let encode = toBase64;
let decode = fromBase64;
