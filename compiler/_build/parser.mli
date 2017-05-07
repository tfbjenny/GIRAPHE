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
  | GREATER
  | GREATEREQUAL
  | SMALLER
  | SMALLEREQUAL
  | EQUAL
  | NOTEQUAL
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
  | ADDNODE
  | ADDEDGE
  | FINDSPECIFIC
  | FINDPATH
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
  | LEFTBRACKET
  | RIGHTBRACKET
  | LEFTCURLYBRACKET
  | RIGHTCURLYBRACKET
  | LEFTROUNDBRACKET
  | RIGHTROUNDBRACKET
  | EOF
  | ID of (string)
  | INT_LITERAL of (int)
  | STRING_LITERAL of (string)
  | FLOAT_LITERAL of (float)
  | BOOL_LITERAL of (bool)

val program :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf ->  Ast.program
