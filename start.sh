#!/bin/bash

echo -e "\nCompiling code.\n"

gcc src/main.c src/get_size_of_matrix.c src/get_count_of_matrix.c src/get_matrix.c -o src/main.out

echo -e "Code has complied.\n"
	
src/main.out

