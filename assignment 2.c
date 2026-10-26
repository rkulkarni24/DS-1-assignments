/*
	Assignment 2 - Sparse Matrix Operations
	Problem Statement - 
	Write a C program for sparse matrix realization and operations on it- Transpose, Fast Transpose
*/

#include <stdio.h>
#include <stdlib.h>

void acceptMat(int mat[20][20], int r, int c) 
{
	printf("Enter matrix elements:\n");
	for(int i = 0; i < r; i++) 
	{
		for(int j = 0; j < c; j++) 
		{
			scanf("%d", &mat[i][j]);
		}
	}
	printf("\n");
}

void displayMat(int mat[20][20], int r, int c) 
{
	printf("Matrix elements:\n");
	for(int i = 0; i < r; i++) 
	{
		for(int j = 0; j < c; j++) 
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int genCompact(int mat[20][20], int r, int c, int res[20][20])
{
	int k=1;
	res[0][0] = r;
	res[0][1] = c;
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			if(mat[i][j] != 0)
			{
				res[k][0] = i;
				res[k][1] = j;
				res[k][2] = mat[i][j];
				k++;
			}
		}
	}
	res[0][2] = k-1;
	
	return k;
}

int simpleTranspose(int mat[20][20], int r, int c, int st[20][20])
{
	int res[20][20];
	
	genCompact(mat, r, c, res);
	
	st[0][0] = res[0][1];
	st[0][1] = res[0][0];
	st[0][2] = res[0][2];
	
	int k=1;
	for(int i=0; i<res[0][1]; i++)
	{
		for(int j=1; j<=res[0][2]; j++)
		{
			if(res[j][1] == i)
			{
				st[k][0] = res[j][1];
				st[k][1] = res[j][0];
				st[k][2] = res[j][2];
				k++;
			}
		}
	}
	return k;
}

int fastTranspose(int mat[20][20], int r, int c, int st[20][20])
{
	int res[20][20];
	
	genCompact(mat, r, c, res);
	
	st[0][0] = res[0][1];
	st[0][1] = res[0][0];
	st[0][2] = res[0][2];
	
	int k =1;
	int col = res[0][1];
	int t = res[0][2];
	
	int cols[col];
	for(int i=0; i<col; i++)
	{
		cols[i]=0;
	}
	
	int startPos[col];
	startPos[0] = 1;
	for(int j=1; j<=t; j++)
	{
		cols[res[j][1]]++;
	}
	
	for(int k=1; k<col; k++)
	{
		startPos[k] = startPos[k-1] + cols[k-1];
	} 

	for(int j=1; j<=t; j++)
	{
		int target = res[j][1];			 
		int pos = startPos[target];

		st[pos][0] = res[j][1];
		st[pos][1] = res[j][0];
		st[pos][2] = res[j][2];

		startPos[target]++;
	}
	return t+1;
}

int main() 
{   
    int mat1[20][20], mat2[20][20];
    int r1, c1, r2, c2;
    int ch;

    printf("Enter order of first matrix:\n");
    scanf("%d %d",&r1,&c1);
    
    
    printf("Enter order of second matrix:\n");
    scanf("%d %d",&r2,&c2);
    
    int res1[20][20];
    int res2[20][20];
    int res3[20][20];
    int res4[20][20];
	int res5[20][20];
	int res6[20][20];
    
    int k1, k2;
    int k3, k4;
	int k5, k6;
    
    do
    {
    	printf("Enter 1 for accept elements\nEnter 2 for print matrix\nEnter 3 compact form\nEnter 4 for simple transpose\nEnter 5 for fast transpose\n");
    	scanf("%d",&ch);
    	
    	switch(ch)
    	{
    		case 1:
    			acceptMat(mat1, r1, c1);
    			acceptMat(mat2, r2, c2);
    			
    			break;
    			
    		case 2:
    			displayMat(mat1, r1, c1);
				displayMat(mat2, r2, c2);
			
			break;
				
			case 3:
				k1 = genCompact(mat1, r1, c1, res1);
				displayMat(res1, k1, 3);
				
				k2 = genCompact(mat2, r2, c2, res2);
				displayMat(res2, k2, 3);
			
				break;
		
			case 4:
				k3  = simpleTranspose(mat1, r1, c1, res3);
				displayMat(res3, k3, 3);
			
				k4 = simpleTranspose(mat2, r2, c2, res4);
				displayMat(res4, k4, 3);
			
				break;
		
			case 5:
				k5 = fastTranspose(mat1, r1, c1, res5);
				displayMat(res5, k5, 3);
			
				k6 = fastTranspose(mat2, r2, c2, res6);
				displayMat(res6, k6, 3);
			
				break;
			
			default:
				break;
				
		}
		
	}while(ch<=5 && ch>0);
   
    return 0;
}
