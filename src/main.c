#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_size_of_matrix.h"
#include "get_count_of_matrix.h"
#include "get_matrix.h"

void finish()
{
	printf("\n------------------------------\n\nProgram is finish thank for use !!\n\n------------------------------\n\n");
}

int main()
{
	printf("\n------------------------------\n\nHello welcome to \"Matrix calculate program\"\n");
	printf("This is all command you can use ---> add , minus , multiply , determinant , quit\n");	
	char *command = (char*)malloc(16 * sizeof(int));
	if(command == NULL)
	{
		printf("Allocate memory error\n------------------------------\n"); 
		return 1;	
	}	
	
	int vaild = 0;
	
	printf("Type your command here ---> ");	
	while(!vaild)
	{
		scanf("%s",command);
		
		if(strcmp(command, "add") == 0)
		{
			system("gcc src/add_matrix.c src/get_size_of_matrix.c src/get_count_of_matrix.c src/get_matrix.c -o src/add_matrix.out && src/add_matrix.out");
			printf("\n------------------------------\n\nProgram additional matrix is complete\n\n------------------------------\n\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "minus") == 0)
		{
			system("gcc src/minus_matrix.c src/get_size_of_matrix.c src/get_count_of_matrix.c src/get_matrix.c -o src/minus_matrix.out && src/minus_matrix.out");	
			printf("\n------------------------------\n\nProgram minus matrix is complete\n\n------------------------------\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "multiply") == 0)
		{
			system("gcc src/multiply_matrix.c src/get_size_of_matrix.c src/get_count_of_matrix.c src/get_matrix.c -o src/multiply_matrix.out && src/multiply_matrix.out");	
			printf("\n------------------------------\n\nProgram multiply matrix is complete\n\n------------------------------\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "determinant") == 0)
		{
			system("gcc src/determinant_matrix.c src/get_size_of_matrix.c src/get_count_of_matrix.c src/get_matrix.c -o src/determinant_matrix.out && src/determinant_matrix.out");	
			printf("\n------------------------------\n\nProgram determinant matrix is complete\n\n------------------------------\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}
		else if(strcmp(command, "quit") == 0)
		{
			vaild = 1;
			finish();	
		}	
		else
		{
			printf("\n------------------------------\n\nYou type invaild command please type only this command ( add , minus , multiply , determinant )\nIf you type vaild command but the code will erroe contact us ---> https://github.com/Loveberland\n");	
			printf("Type your command here ---> ");	
		}
	
	}
	free(command);
	return 0;
}

