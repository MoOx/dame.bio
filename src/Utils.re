[@bs.val] external encodeURIComponent: string => string = "";

let encodeURI = uri => encodeURIComponent(uri);

let stringMapPartial = (f, s) => {
  let b = Buffer.create(String.length(s));
  let addPerhaps = c =>
    switch (f(c)) {
    | None => ()
    | Some(c') => Buffer.add_char(b, c')
    };

  String.iter(addPerhaps, s);
  Buffer.contents(b);
};

let tagifyChar = c =>
  switch (c) {
  | ' ' => None
  | _ => Some(c)
  };

let tagifyString = string => stringMapPartial(tagifyChar, string);
