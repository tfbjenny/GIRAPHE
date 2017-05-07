(* Binary Operators *)
type binop =
  Add         (* + *)
| Sub         (* - *)
| Mult        (* * *)
| Div         (* / *)
| Mod         (* % *)
| Equal       (* == *)
| Neq         (* != *)
| Less        (* < *)
| Leq         (* <= *)
| Greater     (* > *)
| Geq         (* >= *)
| And         (* and *)
| Or          (* or *)
(* Graph Only *)

(* Unary Operators *)
type unop =
  Neg         (* - *)
| Not         (* not *)

(* Numbers int | float *)
type num =
  Num_Int of int          (* 514 *)
| Num_Float of float      (* 3.1415 *)

(* Variable Type *)
type var_type =
  Int_t                   (* int *)
| Float_t                 (* float *)
| String_t                (* string *)
| Bool_t
| Node_t
| Graph_t
| Dict_Int_t
| Dict_Float_t
| Dict_String_t
| Dict_Node_t
| Dict_Graph_t
| List_Int_t
| List_Float_t
| List_String_t
| List_Bool_t
| List_Node_t
| List_Graph_t
| Void_t
| Null_t

(* Type Declaration *)
type formal =
| Formal of var_type * string   (* int aNum *)


type expr =
    Num_Lit of num
|   Null
|   String_Lit of string
|   Bool_lit of bool
|   Node of expr
| 	Graph_Link of expr * graph_op * expr * expr
|   EdgeAt of expr * expr * expr
| 	Binop of expr * binop * expr
|  	Unop of unop * expr
|   Id of string
|   Assign of string * expr
|   Noexpr
|   ListP of expr list
|   DictP of (expr * expr) list
|   Call of string * expr list    (* function call *)
|   CallDefault of expr * string * expr list
|   Ganalysis of expr list
|   Eanalysis of string * expr * string

and edge_graph_list = {
  graphs: expr list;
  edges: expr list;
}

type var_decl =
| Local of var_type * string * expr

(* Statements *)
type stmt =
  Expr of expr     (* set foo = bar + 3 *)
| Return of expr
| For of expr * expr * expr * stmt list
| If of expr * stmt list * stmt list
| While of expr * stmt list
| Var_dec of var_decl
| Func of func_decl

(* Function Declaration *)
and func_decl = {
  returnType: var_type;
  name: string;
  args: formal list;
  body: stmt list;
}


(* Program entry point *)
type program = stmt list
