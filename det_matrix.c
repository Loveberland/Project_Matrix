#include <stdio.h>
#include <stdlib.h>
void get_rows_cols(int *rows, int *cols)
{
	printf("Type your rows : ");
	scanf("%d",rows);
	printf("Type your cols : ");
	scanf("%d",cols);
}

void get_matrix(int **mat, int rows, int cols)
{
	printf("--------------------\n");
	printf("Type your matrix\n");
	for(int i = 0 ; i < rows ; i++)
	{
		printf("* ");	
	}
	printf(" <--- This is your rows\n");
	for(int i = 0 ; i < rows ; i++)
	{
		for(int j = 0 ; j < cols ; j++)
		{
			scanf("%d",&mat[i][j]);
		}
	}
}

void det(int **result, int **mat, int rows, int cols)
{
	printf("--------------------\n");
	printf("Result of determinant\n");
	for(int i = 0 ; i < rows + 2 ; i++)
	{
		for(int j = 1 ; j < cols + 2 ; j++)
		{

		}
	}	
}

void main()
{
	int rows, cols;
	get_rows_cols(&rows,&cols);
	
	int **mat, **result;
	mat = (int**)malloc(rows * sizeof(int*));
	if(mat == NULL)
	{
		printf("Memories allocate faild\n");
		exit(1);
	}
	for(int i = 0 ; i < cols ; i++)
	{
		mat[i] = (int*)malloc(cols * sizeof(int));
		if(mat[i] == NULL)
		{
			printf("Memories allocate faild");
			exit(1);
		}
	}

	get_matrix(mat,rows,cols);

	result = (int**)malloc(rows * sizeof(int*));
	if(result == NULL)
	{
		printf("Memories allocate faild");
		exit(1);	
	}
	for(int i = 0 ; i < cols ; i++)
	{
		result[i] = (int*)malloc(cols * sizeof(int));
		if(result == NULL)
		{
			printf("Memories allocate faild");
			exit(1);
		}
	}

	det(result, mat, rows, cols);	
}

