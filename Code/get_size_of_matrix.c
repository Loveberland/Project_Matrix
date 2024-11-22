#include <stdio.h>
#include <stdlib.h>
#include "get_size_of_matrix.h"

void get_size_of_matrix(int *rows, int *cols)
{
	printf("\n------------------------------\n\n");
	while(1)
	{
		printf("Type your rows here (please type only number) ---> ");
		if(scanf("%d",rows) == 1)
		{
			break;	
		}
		else
		{
			while(getchar() != '\n')
			{
				printf("You type invaild\n");	
			}
		}
	}
	
	while(1)
	{
		printf("Type your cols here (please type only number) ---> ");
		if(scanf("%d",cols) == 1)
		{
			break;	
		}
		else
		{
			while(getchar() != '\n')
			{
				printf("You type invaild\n");	
			}
		}
	}

	printf("\n------------------------------\n\n");
}

