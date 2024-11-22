#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_count_of_matrix.h"
void get_count_of_matrix(int *count)
{
	while(1)
	{
		printf("Type count of matrix here (please type only number) ---> ");
		if(scanf("%d",count) == 1)
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
}

