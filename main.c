#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE file;	
	printf("Welcome to my project this is calculate matrix\n");
	printf("--------------------\n");	
	printf("This is all command you can use ---> add , minus , multiply , det , exit\n");
	printf("--------------------\n");
	char *command = (char*)malloc(10 * sizeof(char));
	if(command == NULL)
	{
		printf("--------------------\n");	
		printf("Allocate memmory fault!!\n");
		printf("--------------------\n");
		printf("Program is finish!!");
		exit(1);
	}	
	while(1)
	{
		printf("Type your command here ---> ");	
		scanf("%s",command);
		if(strcmp(command, "add") == 0)
		{
			int ret = system("gcc add_matrix.c -o add_matrix && ./add_matrix");
			if(ret != 0)
			{
				printf("Program is error contact us ---> https://www.facebook.com/profile.php?id=100074726351560\n");
			}
			break;	
		}
		else if(strcmp(command, "minus") == 0)
		{
			int ret = system("gcc minus_matrix.c -o minus_matrix && ./minus_matrix");
			if(ret != 0)
			{
				printf("Program is error contact us ---> https://www.facebook.com/profile.php?id=100074726351560\n");
			}
			break;	
		}
		else if(strcmp(command, "multiply") == 0)
		{
			int ret = system("gcc multiply_matrix.c -o multiply_matrix && ./multiply_matrix");
			if(ret != 0)
			{
				printf("Program is error contact us ---> https://www.facebook.com/profile.php?id=100074726351560\n");
			}
			break;
		}	
		else if(strcmp(command, "det") == 0)
		{
			int ret = system("gcc det_matrix.c -o det_matrix && ./det_matrix");
			if(ret != 0)
			{
				printf("Program is error contact us ---> https://www.facebook.com/profile.php?id=100074726351560\n");
			}
			break;
		}	
		else if(strcmp(command, "exit") == 0)
		{
			printf("Program is finish\n");	
			break;
		}
		else
		{
			printf("Unknow command\n");
		}	
	}	
}

