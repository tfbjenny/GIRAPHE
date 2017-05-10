module A = Ast
module S = Sast

module StringMap = Map.Make(String)
let node_num = ref 0

let convert_binop = function
    A.Add -> S.Add
  | A.Sub -> S.Sub
  | A.Mult -> S.Mult
  | A.Div -> S.Div
  | A.Mod -> S.Mod
  | A.Equal -> S.Equal
  | A.Neq -> S.Neq
  | A.Less -> S.Less
  | A.Leq -> S.Leq
  | A.Greater -> S.Greater
  | A.Geq -> S.Geq
  | A.And -> S.And
  | A.Or -> S.Or
  | A.ListNodesAt -> S.ListNodesAt   (* *)
  | A.ListEdgesAt -> S.ListEdgesAt      (* *)
  | A.RootAs -> S.RootAs                        (* *)

let convert_unop = function
  A.Neg -> S.Neg
| A.Not -> S.Not

let convert_num = function
    A.Num_Int(a) -> S.Num_Int(a)
  | A.Num_Float(a) -> S.Num_Float(a)

let convert_var_type = function
    A.Int_t -> S.Int_t
  | A.Float_t -> S.Float_t
  | A.String_t -> S.String_t
  | A.Bool_t -> S.Bool_t
  | A.Node_t -> S.Node_t
  | A.Graph_t -> S.Graph_t
  | A.List_Int_t -> S.List_Int_t
  | A.List_Float_t -> S.List_Float_t
  | A.List_String_t -> S.List_String_t
  | A.List_Node_t -> S.List_Node_t
  | A.List_Graph_t -> S.List_Graph_t
  | A.List_Bool_t -> S.List_Bool_t
  | A.Dict_Int_t -> S.Dict_Int_t
  | A.Dict_Float_t -> S.Dict_Float_t
  | A.Dict_String_t -> S.Dict_String_t
  | A.Dict_Node_t -> S.Dict_Node_t
  | A.Dict_Graph_t -> S.Dict_Graph_t
  | A.Void_t -> S.Void_t
  | A.Null_t -> S.Null_t
  
  
  
  let convert_graph_op = function               (* *)
| A.Right_Link -> S.Right_Link                  (* *)



let rec get_entire_name m aux cur_name =
  if (StringMap.mem cur_name m) then
    let aux = (StringMap.find cur_name m) ^ "." ^ aux in
    (get_entire_name m aux (StringMap.find cur_name m))
  else aux

let increase_node_num =
  let node_num = ref(!node_num) in
  !(node_num) - 1

let rec convert_expr m = function
    A.Num_Lit(a) -> S.Num_Lit(convert_num a)
|   A.Null -> S.Null
|   A.String_Lit(a) -> S.String_Lit(a)
|   A.Bool_lit(a) -> S.Bool_lit(a)
|   A.Node(a) -> node_num := (!node_num + 1); S.Node(!node_num - 1, convert_expr m a)
|   A.Graph_Link(a,b,c,d) -> S.Graph_Link(                           (* *) 
      convert_expr m a,
      convert_graph_op b,
      convert_expr m c,
      (match (c,d) with
        | (A.ListP(_), A.ListP(_))
        | (A.ListP(_), A.Noexpr)
        | (A.ListP(_), A.Null) -> convert_expr m d
        | (A.ListP(_), _) -> S.ListP([convert_expr m d])
        | _ -> convert_expr m d
      ))                                                             (* *)
|   A.EdgeAt(a,b,c) -> S.EdgeAt(convert_expr m a, convert_expr m b, convert_expr m c) 
|   A.Binop(a,b,c) -> S.Binop(convert_expr m a, convert_binop b, convert_expr m c)
|   A.Unop(a,b) -> S.Unop(convert_unop a, convert_expr m b)
|   A.Id(a) -> S.Id(a)
|   A.Assign(a,b) -> S.Assign(a, convert_expr m b)
|   A.Noexpr -> S.Noexpr
|   A.ListP(a) -> S.ListP(convert_expr_list m a)
|   A.DictP(a) -> S.DictP(convert_dict_list m a)
|   A.Call(a,b) -> S.Call(get_entire_name m a a, convert_expr_list m b)
|   A.CallDefault(a,b,c) -> S.CallDefault(convert_expr m a, b, convert_expr_list m c)



and convert_expr_list m = function
    [] -> []
  | [x] -> [convert_expr m x]
  | _ as l -> (List.map (convert_expr m) l)

and convert_dict m = function
  (c,d) -> (convert_expr m c, convert_expr m d)

and convert_dict_list m = function
    [] -> []
  | [x] -> [convert_dict m x]
  | _ as l -> (List.map (convert_dict m) l)
  
and convert_e m = function
    (c,d,e) ->(convert_expr m c, convert_expr m d, convert_expr m e)

and convert_e_list m = function
    [] -> []
  | [x] -> [convert_e m x]
  | _ as l -> (List.map (convert_e m) l)
    

let convert_edge_graph_list m = function
  {A.graphs = g; A.edges = e} -> {S.graphs = convert_expr_list m g; S.edges = convert_expr_list m e}

let convert_formal = function
  | A.Formal(v, s) -> S.Formal(convert_var_type v, s)

let convert_formal_list = function
    [] -> []
  | [x] -> [convert_formal x]
  | _ as l -> (List.map convert_formal l)

(* create a main funcition outside of the whole statement list *)
let createMain stmts = A.Func({
    A.returnType = A.Int_t;
    A.name = "main";
    A.args = [];
    A.body = stmts;
  })

let rec get_funcs_from_body_a = function
    [] -> []
  | A.Func(_) as x::tl -> x :: (get_funcs_from_body_a tl)
  | _::tl -> get_funcs_from_body_a tl

let rec get_body_from_body_a = function
    [] -> []
  | A.Func(_)::tl -> get_body_from_body_a tl
  | _ as x::tl -> x :: (get_body_from_body_a tl)

let rec mapper parent map = function
   [] -> map
 | A.Func{A.name = n; _}::tl ->
    mapper parent (StringMap.add n parent map) tl
 | _-> map

let convert_bfs_insider my_map = function
    A.Func{A.name = n; A.body = b; _}->
    let curr = get_funcs_from_body_a b in
      let my_map = mapper n my_map curr in
    (curr,my_map)
  | _->([],my_map)

let rec bfser m result = function
    [] ->(List.rev result, m)
  | A.Func{A.returnType = r; A.name = n; A.args = args; A.body = b} as a ::tl -> let result1 = convert_bfs_insider m a in
    let latterlist = tl @ (fst result1) in
    let m = (snd result1) in
    let addedFunc = A.Func({
      A.returnType = r; A.name = n; A.args = args; A.body = get_body_from_body_a b
    }) in
    let result = result @ [addedFunc] in
     bfser m result latterlist
  | _->([], m)

(* convert stament in A to C, except those Var_dec and Func, we will convert them separately *)
let rec convert_stmt m = function
    A.Expr(a) -> S.Expr(convert_expr m a)
  | A.Return(a) -> S.Return(convert_expr m a)
  | A.For(e1, e2, e3, stls) -> S.For(convert_expr m e1, convert_expr m e2, convert_expr m e3, List.map (convert_stmt m) stls)
  | A.If(e, stls1, stls2) -> S.If(convert_expr m e, List.map (convert_stmt m) stls1, List.map (convert_stmt m) stls2)
  | A.While(e, stls) -> S.While(convert_expr m e, List.map (convert_stmt m) stls)
  | _ -> S.Expr(S.Noexpr)


let rec get_body_from_body_c m = function
    [] -> []
  | A.Var_dec(A.Local(_, name, v))::tl when v <> A.Noexpr -> S.Expr(S.Assign(name, convert_expr m v)) :: (get_body_from_body_c m tl)
  | A.Var_dec(A.Local(_, _, v))::tl when v = A.Noexpr -> (get_body_from_body_c m tl)
  | _ as x::tl -> (convert_stmt m x) :: (get_body_from_body_c m tl)

let rec get_local_from_body_c = function
    [] -> []
  | A.Var_dec(A.Local(typ, name, _))::tl -> S.Formal(convert_var_type typ, name) :: (get_local_from_body_c tl)
  | _::tl -> get_local_from_body_c tl

(* convert the horizental level function list in A to C *)
let rec convert_func_list_c m = function
    [] -> []
  | A.Func{A.returnType = r; A.name = n; A.args = a; A.body = b} :: tl -> {
    S.returnType = convert_var_type r;
    S.name = get_entire_name m n n;
    S.args = convert_formal_list a;
    S.body = get_body_from_body_c m b;
    S.locals = get_local_from_body_c b;
    S.pname = if n = "main" then "main" else get_entire_name m (StringMap.find n m) (StringMap.find n m)
  } :: (convert_func_list_c m tl)
  | _::tl -> convert_func_list_c m tl

(* entry point *)
let convert stmts =
  let funcs = createMain stmts in
  let horizen_funcs_m = bfser StringMap.empty [] [funcs] in
  convert_func_list_c (snd horizen_funcs_m) (fst horizen_funcs_m)
