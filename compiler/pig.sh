make clean
ocamlc -c ast.ml
ocamlc -c sast.ml
ocamlyacc parser.mly
ocamllex scanner.mll
ocamlc -c parser.mli # compile parser types
ocamlc -c scanner.ml
ocamlc -c parser.ml
ocamlc -c checker.ml
ocamlc -c parserize_sast.ml
ocamlc -o pig ast.cmo sast.cmo parser.cmo scanner.cmo checker.cmo parserize_sast.cmo
#./pig
