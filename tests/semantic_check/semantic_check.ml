(* Program entry point *)
open Printf

let _ =
    let lexbuf = Lexing.from_channel stdin in
    let ast = Parser.program Scanner.token lexbuf in
    let sast = Checker.convert ast in
    try 
        Semant.check sast
    with 
        Semant.SemanticError(m) -> print_endline m
        (* Semant.SemanticError(m) -> raise (Failure(m)) *)
