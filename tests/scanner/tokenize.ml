open Parser

let stringify = function
  (* calculation *)
  | PLUS -> "PLUS"   | MINUS -> "MINUS"
  | TIMES -> "TIMES" | DIVIDE -> "DIVIDE"
  | MOD -> "MOD"
  (* separator *)
  | SEMICOLON -> "SEMICOLON" | SEQUENCE -> "SEQUENCE"
  | ASSIGN -> "ASSIGN"         | COLON -> "COLON"
  | DOT -> "DOT"
  (* logical operation *)
  | AND -> "AND"      | OR -> "OR"
  | NOT -> "NOT"      | IF -> "IF"
  | ELSE -> "ELSE"    | FOR -> "FOR"
  | WHILE -> "WHILE"  | BREAK -> "BREAK"
  | CONTINUE -> "CONTINUE" | IN -> "IN"
  (* comparator *)
  | EQ -> "EQUAL"          | NEQ -> "NOTEQUAL"
  | GT -> "GREATER"      | GEQ -> "GREATEREQUAL"
  | LT -> "SMALLER"      | LEQ -> "SMALLEREQUAL"
  (* graph operator *)
  | RIGHTLINK -> "RIGHTLINK"
  | AT -> "AT"
  | AMPERSAND -> "AMPERSAND"  | SIMILARITY -> "SIMILARITY"
  (* identifier *)
  | ID(string) -> "ID"
  (* primary type *)
  | INT -> "INT"          | FLOAT -> "FLOAT"
  | STRING -> "STRING"    | BOOL -> "BOOL"
  | NODE -> "NODE"        | GRAPH -> "GRAPH"
  | LIST -> "LIST"        | DICT -> "DICT"
  | NULL -> "NULL"        | VOID -> "VOID"
  (* quote *)
  | QUOTE -> "QUOTE"
  (* boolean operation *)
  (* bracket *)
  | LBRACKET -> "LEFTBRACKET"           | RBRACKET -> "RIGHTBRACKET"
  | LBRACE -> "LEFTCURLYBRACKET" | RBRACE -> "RIGHTCURLYBRACKET"
  | LPAREN -> "LEFTROUNDBRACKET" | RPAREN -> "RIGHTROUNDBRACKET"
  (* End-of-File *)
  | EOF -> "EOF"
  (* Literals *)
  | INT_LITERAL(int) -> "INT_LITERAL"
  | FLOAT_LITERAL(float) -> "FLOAT_LITERAL"
  | STRING_LITERAL(string) -> "STRING_LITERAL"
  | BOOL_LITERAL(bool) -> "BOOL_LITERAL"
  | RETURN -> "RETURN"

let _ =
  let lexbuf = Lexing.from_channel stdin in
  let rec print_tokens = function
    | EOF -> " "
    | token ->
      print_endline (stringify token);
      print_tokens (Scanner.token lexbuf) in
  print_tokens (Scanner.token lexbuf)
