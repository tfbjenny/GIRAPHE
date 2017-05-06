#!/bin/bash

NC='\033[0m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'

result=true

INPUT_FILES="lib/*.in"
printf "${CYAN}Running code_gen tests...\n${NC}"



for input_file in $INPUT_FILES; do
    output_file=${input_file/.in/.out}
    sh ./circline.sh $input_file | cat > test_lib.out
done

exit 0

# if $result; then
# 	exit 0
# else
# 	exit 1
# fi
