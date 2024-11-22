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
		printf("Allocate memory error\nPlease contact us ---> https://github.com/Loveberland\n------------------------------\n"); 
		return 1;	
	}	
	
	int vaild = 0;
	
	printf("Type your command here ---> ");	
	while(!vaild)
	{
		scanf("%s",command);
		
		if(strcmp(command, "add") == 0)
		{
			system("gcc Code/add_matrix.c Code/get_size_of_matrix.c Code/get_count_of_matrix.c Code/get_matrix.c -o Code/add_matrix.out && Code/add_matrix.out");
			printf("\n------------------------------\n\nProgram additional matrix is complete\n\n------------------------------\n\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "minus") == 0)
		{
			system("gcc Code/minus_matrix.c Code/get_size_of_matrix.c Code/get_count_of_matrix.c Code/get_matrix.c -o Code/minus_matrix.out && Code/minus_matrix.out");	
			printf("\n------------------------------\n\nProgram minus matrix is complete\n\n------------------------------\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "multiply") == 0)
		{
			system("gcc Code/multiply_matrix.c Code/get_size_of_matrix.c Code/get_count_of_matrix.c Code/get_matrix.c -o Code/multiply_matrix.out && Code/multiply_matrix.out");	
			printf("\n------------------------------\n\nProgram multiply matrix is complete\n\n------------------------------\n");
			printf("\nIf you want to use this program more type command here (if no type \"quit\") ---> ");	
		}	
		else if(strcmp(command, "determinant") == 0)
		{
			system("gcc Code/determinant_matrix.c Code/get_size_of_matrix.c Code/get_count_of_matrix.c Code/get_matrix.c -o Code/determinant_matrix.out && Code/determinant_matrix.out");	
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

