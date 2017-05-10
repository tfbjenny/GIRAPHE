# Check whether the file "utils.bc" exist
file="utils.bc"
if [ ! -e "$file" ]
then
	clang -emit-llvm -o utils.bc -c lib/utils.c
fi

if [ $# -eq 1 ]
then
    ./giraphe.native <$1 >a.ll
else
    ./giraphe.native $1 <$2 >a.ll
fi
clang -Wno-override-module utils.bc a.ll -o $1.exe
./$1.exe
rm a.ll
rm ./$1.exe

# /usr/local/opt/llvm38/bin/clang-3.8
