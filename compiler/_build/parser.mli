type token =
  | PLUS
  | MINUS
  | TIMES
  | DIVIDE
  | MOD
  | SEMICOLUMN
  | SEQUENCE
  | ASSIGN
  | COLUMN
  | DOT
  | SPLIT
  | GT
  | GEQ
  | LT
  | LEQ
  | EQ
  | NEQ
  | AND
  | OR
  | NOT
  | IF
  | ELSE
  | FOR
  | WHILE
  | BREAK
  | CONTINUE
  | IN
  | RETURN
  | WEIGHTED
  | LINK
  | RIGHTLINK
  | LEFTLINK
  | SIMILARITY
  | AT
  | AMPERSAND
  | INT
  | FLOAT
  | STRING
  | BOOL
  | NODE
  | EDGE
  | GRAPH
  | LIST
  | DICT
  | NULL
  | VOID
  | QUOTE
  | LBRACKET
  | RBRACKET
  | LBRACE
  | RBRACE
  | LPAREN
  | RPAREN
  | EOF
  | ID of (string)
  | INT_LITERAL of (int)
  | STRING_LITERAL of (string)
  | FLOAT_LITERAL of (float)
  | BOOL_LITERAL of (bool)

val program :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf ->  Ast.program
