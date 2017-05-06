
%{ open Ast %}

/* Arithmetic Operators */
%token PLUS MINUS TIMES DIVIDE MOD

/* Separator */
%token SEMICOLUMN SEQUENCE ASSIGN COLUMN DOT SPLIT

/* Comparative Operators */
%token GREATER GREATEREQUAL SMALLER SMALLEREQUAL EQUAL NOTEQUAL

/* Logical Operators & Function Keywords*/
%token AND OR NOT IF ELSE FOR WHILE BREAK CONTINUE IN RETURN

/* Graph operator */
%token WEIGHED ADDNODE ADDEDGE FINDSPECIFIC FINDPATH

/* Primary Type */
%token INT FLOAT STRING BOOL NODE EDGE GRAPH LIST DICT NULL VOID

/* Quote */
%token QUOTE

/* Bracket */
%token LEFTBRACKET RIGHTBRACKET LEFTCURLYBRACKET RIGHTCURLYBRACKET LEFTROUNDBRACKET RIGHTROUNDBRACKET

/* EOF */
%token EOF

/* Identifiers */
%token <string> ID

/* Literals */
%token <int> INT_LITERAL
%token <string> STRING_LITERAL
%token <float> FLOAT_LITERAL
%token <bool> BOOL_LITERAL

/* Order */
%left SEQUENCE  /* , order */
%right ASSIGN
%left AND OR
%left EQUAL NOTEQUAL
%left GREATER SMALLER GREATEREQUAL SMALLEREQUAL
%left PLUS MINUS
%left TIMES DIVIDE MOD
%right NOT
%right LINK RIGHTLINK LEFTLINK AMPERSAND
%left SIMILARITY AT
%right LEFTROUNDBRACKET
%left  RIGHTROUNDBRACKET
%right COLUMN
%right DOT

%start program
%type < Ast.program> program

%%

/* Program flow */
program:
| stmt_list EOF                         { List.rev $1 }

stmt_list:
| /* nothing */                         { [] }
| stmt_list stmt                        { $2 :: $1 }

stmt:
| expr SEMICOLUMN                       { Expr($1) }
| func_decl                             { Func($1) }
| RETURN SEMICOLUMN                { Return(Noexpr) }
| RETURN expr SEMICOLUMN                { Return($2) }
| FOR LEFTROUNDBRACKET for_expr SEMICOLUMN expr SEMICOLUMN for_expr RIGHTROUNDBRACKET LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET
  {For($3, $5, $7, List.rev $10)}
| IF LEFTROUNDBRACKET expr RIGHTROUNDBRACKET LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET ELSE LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET
  {If($3,List.rev $6,List.rev $10)}
| IF LEFTROUNDBRACKET expr RIGHTROUNDBRACKET LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET
  {If($3,List.rev $6,[])}
| WHILE LEFTROUNDBRACKET expr RIGHTROUNDBRACKET LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET
  {While($3, List.rev $6)}
| var_decl SEMICOLUMN                   { Var_dec($1)}

var_decl:
| var_type ID              { Local($1, $2, Noexpr) }
| var_type ID ASSIGN expr  { Local($1, $2, $4) }

var_type:
| VOID                  {Void_t}
| NULL                  {Null_t}
| INT 								  {Int_t}
| FLOAT 								{Float_t}
| STRING 								{String_t}
| BOOL {Bool_t}
| NODE {Node_t}
| GRAPH {Graph_t}
| DICT SMALLER INT GREATER {Dict_Int_t}
| DICT SMALLER FLOAT GREATER {Dict_Float_t}
| DICT SMALLER STRING GREATER {Dict_String_t}
| DICT SMALLER NODE GREATER {Dict_Node_t}
| DICT SMALLER GRAPH GREATER {Dict_Graph_t}
| LIST SMALLER INT GREATER {List_Int_t}
| LIST SMALLER FLOAT GREATER {List_Float_t}
| LIST SMALLER STRING GREATER {List_String_t}
| LIST SMALLER BOOL GREATER {List_Bool_t}
| LIST SMALLER NODE GREATER {List_Node_t}
| LIST SMALLER GRAPH GREATER {List_Graph_t}

formal_list:
| /* nothing */               { [] }
| formal                      { [$1] }
| formal_list SEQUENCE formal { $3 :: $1 }


formal:
| var_type ID           { Formal($1, $2) }

func_decl:
| var_type ID LEFTROUNDBRACKET formal_list RIGHTROUNDBRACKET LEFTCURLYBRACKET stmt_list RIGHTCURLYBRACKET {
  {
    returnType = $1;
    name = $2;
    args = List.rev $4;
    body = List.rev $7;
  }
}


/* For loop decl*/
for_expr:
| /* nothing */                         { Noexpr }
| expr                                  { $1 }

expr:
  literals {$1}
| NULL                            { Null }
| arith_ops                       { $1 }
| NODE LEFTROUNDBRACKET expr RIGHTROUNDBRACKET { Node($3) }
| ID 					                    { Id($1) }
| ID ASSIGN expr 					        { Assign($1, $3) }
| LEFTBRACKET list RIGHTBRACKET   			{ ListP(List.rev $2) }
| LEFTCURLYBRACKET dict RIGHTCURLYBRACKET 	{ DictP(List.rev $2) }
| LEFTROUNDBRACKET expr RIGHTROUNDBRACKET 	{ $2 }
| ID LEFTROUNDBRACKET list RIGHTROUNDBRACKET              { Call($1, List.rev $3) }
| INT LEFTROUNDBRACKET list RIGHTROUNDBRACKET              { Call("int", List.rev $3) }
| FLOAT LEFTROUNDBRACKET list RIGHTROUNDBRACKET              { Call("float", List.rev $3) }
| BOOL LEFTROUNDBRACKET list RIGHTROUNDBRACKET              { Call("bool", List.rev $3) }
| STRING LEFTROUNDBRACKET list RIGHTROUNDBRACKET              { Call("string", List.rev $3) }
| expr DOT ID LEFTROUNDBRACKET list RIGHTROUNDBRACKET   {CallDefault($1, $3, List.rev $5)}

/* Lists */
list:
| /* nothing */                         { [] }
| expr                                  { [$1] }
| list SEQUENCE expr                    { $3 :: $1 }


dict_key_value:
| expr COLUMN expr { ($1, $3) }

/* dict */
dict:
| /* nothing */                     { [] }
| dict_key_value 								    { [$1] }
| dict SEQUENCE dict_key_value 			{$3 :: $1}

arith_ops:
| expr PLUS         expr 					{ Binop($1, Add,   $3) }
| expr MINUS        expr 					{ Binop($1, Sub,   $3) }
| expr TIMES        expr 					{ Binop($1, Mult,  $3) }
| expr DIVIDE       expr 					{ Binop($1, Div,   $3) }
| expr EQUAL        expr 					{ Binop($1, Equal, $3) }
| expr NOTEQUAL     expr 					{ Binop($1, Neq,   $3) }
| expr SMALLER      expr 					{ Binop($1, Less,  $3) }
| expr SMALLEREQUAL expr 					{ Binop($1, Leq,   $3) }
| expr GREATER      expr 					{ Binop($1, Greater,  $3) }
| expr GREATEREQUAL expr 					{ Binop($1, Geq,   $3) }
| expr AND          expr 					{ Binop($1, And,   $3) }
| expr MOD          expr 					{ Binop($1, Mod,   $3) }
| expr OR     expr                { Binop($1, Or,    $3) }
| NOT  expr 							        { Unop (Not,   $2) }
| MINUS expr 							        { Unop (Neg, $2) }


literals:
  INT_LITERAL   	   {Num_Lit( Num_Int($1) )}
| FLOAT_LITERAL 	   {Num_Lit( Num_Float($1) )}
| STRING_LITERAL     {String_Lit($1) }
| BOOL_LITERAL       {Bool_lit($1) }
