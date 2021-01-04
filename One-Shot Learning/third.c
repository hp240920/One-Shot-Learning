#include <stdio.h>
#include <stdlib.h>

void printArray(double ** arr, int row, int column)
{

	//printf("Hey");
	for(int i = 0; i < row; i++) {
	for(int j = 0; j < column; j++)
		{
			printf("%0.0lf\t", arr[i][j]);
		}
		printf("\n");
	}
}

void freeItUp(double** arr, int row)
{
	//printf("Hey");
	//int row = sizeof(arr)/sizeof(double *);
	for(int i = 0; i < row; i++) {
		//printf("Hey");
		free(arr[i]);
	}
	free(arr);
	//printf("hello");
	return;
}

double** findInverse(double** arr, int row, int column)
{
	int new_column = 2*column;
	double** inverseArr = (double **)malloc(row * sizeof(double *));
	for(int i = 0; i < row; i++)
	{
		inverseArr[i] = (double *)malloc(new_column * sizeof(double));
	}
	
	int count = column;
	//printf("Hey %d\n", new_column);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < new_column; j++)
		{
			//print("%d", count);
			if(j < column)
			{
				inverseArr[i][j] = arr[i][j];
				continue;
			}
			if(count == j) {
				//printf("Hello");
				inverseArr[i][count] = (double)1;
				continue;
			}else{
				inverseArr[i][j] = (double)0;
				continue;
			}
	}
	//printf("aefdfagagdag\n");
	count++;
}
for(int i = 0; i < row; i++)
{
	double div = inverseArr[i][i];
	for(int j = 0; j < new_column; j++)
	{
		inverseArr[i][j] = inverseArr[i][j]/div;
	}
		//printf("First\n");
		for(int k = i + 1; k < row; k++)
		{
			//printf("Second\n");
			double factor = inverseArr[k][i];
			for(int l = 0; l < new_column; l++)
			{
				//printf("Third\n");
				inverseArr[k][l] -= factor * inverseArr[i][l];
			}
		}
	}
	for(int i = 0; i < row; i++)
	{
		for(int k = 0; k < i; k++)
		{
			double factor = inverseArr[k][i];
			for(int l = 0; l < new_column; l++)
			{
				inverseArr[k][l] -= factor * inverseArr[i][l];
			}
		}
	}

for(int i = 0; i < row; i++)
{
	for(int j = 0; j < column; j++)
	{
		arr[i][j] = inverseArr[i][column + j];
	}
}
freeItUp(inverseArr, row);
	return arr;
}

double** multiply(double** arr1, double** arr2, int arr1Row, int arr1Column, int arr2Row, int arr2Column)
{
	//int arr1Row = sizeof(arr1)/sizeof(double *);
	//int arr1Column = sizeof(arr1[0])/sizeof(double);
	//int arr2Row = sizeof(arr2)/sizeof(double *);
	//int arr2Column = sizeof(arr2[0])/sizeof(double);
	double** productM = NULL;
	//printf("Hey");
	if(arr1Column == arr2Row) {
		productM = (double **)malloc(arr1Row * sizeof(double *));
		for(int i = 0; i < arr1Row; i++)
		{
			productM[i] = (double *)malloc(arr2Column * sizeof(double));
		}

		for(int i = 0; i < arr1Row; i++)
		{
			for(int j = 0; j < arr2Column; j++)
			{
				productM[i][j] = 0;
			}
		}
	
		for(int i = 0; i < arr1Row; i++)
		{
			for(int j = 0; j < arr2Column; j++)
			{
				for(int k = 0; k < arr1Column; k++)
				{
					productM[i][j] += arr1[i][k]*arr2[k][j];
				}
			}
		}
}else{
	return NULL;
	}
	return productM;
}

double** findT(double** arr, int row, int column)
{
	double** result = malloc(column * sizeof(double *));
	for(int i = 0; i < column; i++)
	{
		result[i] = malloc(row * sizeof(double));
	}
	//printf("Hey\n");
	for(int i = 0; i < row; i++)
	{
		//printf("hey");
		for(int j = 0; j < column; j++)
		{
			//printf("hey");
			result[j][i] = arr[i][j];
		}
	}
	return result;
}

int main(int agc, char* argv[])
{
	FILE* trainR = fopen(argv[1], "r");
	if(trainR == NULL)
	{
		return 0;
	}

FILE* testR = fopen(argv[2], "r");
if(testR == NULL)
{
	return 0;
}
int attributeSize = 0;
int trainS = 0;
int testDP = 0;
fscanf(trainR, "%d\n", &attributeSize);
fscanf(trainR, "%d\n", &trainS);
fscanf(testR, "%d\n", &testDP);
int num = attributeSize + 1;
double** prices = malloc(trainS * sizeof(double *));
for(int i = 0; i < trainS; i++)
{
	prices[i] = malloc(sizeof(double));
}
double** attributes = malloc(trainS * sizeof(double *));
for(int i = 0; i < trainS; i++) {
	attributes[i] = malloc(num * sizeof(double));
}
for(int i = 0; i < trainS; i++)
{
	for(int j = 0; j < num; j++)
	{
		if(j == 0)
		{
			attributes[i][j] = 1;
			continue;
		}
		if(j != 0) {
			fscanf(trainR, "%lf,", &attributes[i][j]);
		}
	}
	fscanf(trainR, "%lf", &prices[i][0]);
}
//printf("Test Starting\n");
double ** testM = malloc(testDP * sizeof(double *));
for (int i = 0; i < testDP; i++)
{
	testM[i] = malloc(num * sizeof(double));
}
for(int i = 0; i < testDP; i++)
{
	for(int j = 0; j < num; j++)
	{
		if(j == 0)
		{
			testM[i][j] = 1;
			continue;
		}
		if(j != 0)
		{
			fscanf(testR, "%lf,", &testM[i][j]);
		}
	}
}


double** transposeAtt = findT(attributes, trainS, num);
double** transpose_M_Normal = multiply(transposeAtt, attributes, num, trainS, trainS, num);
double** inverseTN = findInverse(transpose_M_Normal, num, num);
double** IT = multiply(inverseTN, transposeAtt, num, num, num, trainS);
double** W = multiply(IT, prices, num, trainS, trainS, 1);
double** finalM = multiply(testM, W, testDP, num, num, 1);
printArray(finalM, testDP, 1);
freeItUp(attributes, trainS);
freeItUp(prices, trainS);
freeItUp(testM, testDP);
freeItUp(transposeAtt,num);
freeItUp(transpose_M_Normal, num);
//freeItUp(inverseTN);
freeItUp(IT, num);
freeItUp(W, num);
freeItUp(finalM, testDP);
fclose(trainR);
fclose(testR);
return 0;

}


