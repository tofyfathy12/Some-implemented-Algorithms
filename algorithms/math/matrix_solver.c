#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <string.h>
#define EPSILON 1e-9

char *to_string(int num)
{
	int digits_num = 0;
	if (num == 0)
		digits_num = 1;
	else
	{
		int temp = num;
		while (temp > 0)
		{
			temp /= 10;
			digits_num++;
		}
	}
	char *string = (char *)calloc(digits_num + 1, sizeof(char));
	string[digits_num] = '\0';
	for (int i = digits_num - 1; i >= 0; i--)
	{
		string[i] = (num % 10) + 48;
		num--;
	}
	return string;
}

void get_double(char *str, double *n)
{
	bool valid = false;
	char input[1000];
	while (!valid)
	{
		printf("%s", str);
		fgets(input, 1000, stdin);
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';
		if (strlen(input) == 0)
		{
			printf("!!! Invalid Input !!!\n");
			printf("    Try Again\n");
			continue;
		}
		bool notdouble = false;
		int dots = 0;
		for (int i = 0; i < strlen(input); i++)
		{
			if (input[i] == '.')
			{
				dots++;
				if (dots > 1)
				{
					notdouble = true;
					break;
				}
			}
			if (!(isdigit(input[i]) || input[i] == '.' || (input[i] == '-' && i == 0)))
			{
				notdouble = true;
				break;
			}
		}
		if (notdouble)
		{
			printf("!!! Invalid Input !!!\n");
			printf("    Try Again\n");
		}
		else
			valid = true;
	}
	*n = atof(input);
}

void get_integer(char *str, long int *n)
{
	bool valid = false;
	char input[1000];
	while (!valid)
	{
		printf("%s", str);
		fgets(input, 1000, stdin);
		input[strlen(input) - 1] = '\0';
		if (strlen(input) == 0)
		{
			printf("!!! Invalid Input !!!\n");
			printf("    Try Again\n");
			continue;
		}
		bool notint = false;
		int dots = 0;
		for (int i = 0; i < strlen(input); i++)
		{
			if (!(isdigit(input[i]) || (input[i] == '-' && i == 0)))
			{
				notint = true;
				break;
			}
		}
		if (notint)
		{
			printf("!!! Invalid Input !!!\n");
			printf("    Try Again\n");
		}
		else
		{
			if (atof(input) > pow(2, 63) - 1)
			{
				printf("!!! OVERFLOW: NUMBER IS SO BIG !!!\n");
				printf("    Try Again\n");
				continue;
			}
			valid = true;
		}
	}
	*n = atol(input);
}

void show_matrix(double **matrix, int rows, int columns)
{

	for (int row = 0; row < rows; row++)
	{
		printf("==========================================\n|");
		for (int column = 0; column < columns; column++)
		{
			double num = matrix[row][column];
			printf("%.3lf ", num);
			printf("| ");
		}
		printf("\n");
	}
	printf("==========================================\n");
}

double **transpose(double **matrix, int rows, int columns)
{
	double **new_matrix = (double **)malloc(columns * sizeof(double *));
	for (int column = 0; column < columns; column++)
	{
		new_matrix[column] = (double *)malloc(rows * sizeof(double));
		for (int row = 0; row < rows; row++)
			new_matrix[column][row] = matrix[row][column];
	}
	return new_matrix;
}
void gauss_elimination(double **matrix, int rows, int columns)
{
	int number_of_operations = rows - 1;
	for (int operation = 0; operation < number_of_operations; operation++)
	{
		int starting_column = operation;
		int non_zero_pivot_row = -1;
		// finding the non zero pivot row
		while (non_zero_pivot_row == -1 && starting_column < columns)
		{
			for (int row = operation; row < rows; row++) // changed according to operation
			{
				if (matrix[row][starting_column] != 0) // changed according to operation
				{
					non_zero_pivot_row = row;
					break;
				}
			}
			if (non_zero_pivot_row == -1)
				starting_column++;
			else
				break;
		}
		// exchange row 0 with non zero pivot row thus element 0 with 3 and 1 with 4 and 2 with 5 ie the number of columns
		if (matrix[operation][starting_column] == 0 && non_zero_pivot_row != -1) // changed according to operation
		{
			for (int column = starting_column; column < columns; column++) // changed according to operation
			{
				double temp = matrix[operation][column];
				matrix[operation][column] = matrix[non_zero_pivot_row][column];
				matrix[non_zero_pivot_row][column] = temp;
			}
		}
		for (int row = operation + 1; row < rows; row++) // changed according to operation
		{
			double subtracted_num = 0;
			double multiplied_num = matrix[row][starting_column] / matrix[operation][starting_column]; // changed according to operation
			for (int column = 0; column < columns; column++)
			{
				subtracted_num = matrix[operation][column] * multiplied_num;
				matrix[row][column] -= subtracted_num;
				if (fabs(matrix[row][column]) < 1e-9)
					matrix[row][column] = 0;
			}
		}
	}
}

void gauss_jordon_elimination(double **matrix, int rows, int columns)
{
	gauss_elimination(matrix, rows, columns);
	int num_of_operations = rows;
	for (int operation = 1; operation < num_of_operations; operation++)
	{
		int pivot_row = rows - operation;
		int pivot_column = 0;
		bool found = false;
		for (int row = rows - operation; row >= 0; row--)
		{
			for (int column = 0; column < columns && column < rows; column++)
			{
				if (!(matrix[row][column] == 0))
				{
					pivot_row = row;
					pivot_column = column;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		for (int row = pivot_row - 1; row >= 0; row--) // changed according to operation
		{
			double multiplied_num = matrix[row][pivot_column] / matrix[pivot_row][pivot_column];
			double subtracted_num = 0;
			for (int column = columns - 1; column >= 0; column--)
			{
				subtracted_num = multiplied_num * matrix[pivot_row][column];
				matrix[row][column] -= subtracted_num;
				if (fabs(matrix[row][column]) < -1e-9)
					matrix[row][column] = 0;
			}
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++) printf("%.2lf ", matrix[i][j]);
			printf("\n");
		}
	}
	for (int i = 0; i < rows; i++)
	{	
		double scalar = 1;
		for (int j  = 0; j < columns; j++)
		{
			if (matrix[i][j] != 0 && j < rows)
			{
				scalar = matrix[i][j];
				break;
			}
			else if (j >= rows) break;
		}
		for (int j = 0; j < columns; j++)
			matrix[i][j] /= scalar;
	}
}

double **get_inverse(double **matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (double *)realloc(matrix[i], (2 * n) * sizeof(double));
		for (int j = n; j < 2 * n; j++)
		{
			if (j == n + i)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
	double **result = (double **)malloc(n * sizeof(double *));
	gauss_jordon_elimination(matrix, n, 2*n);
	for (int i = 0; i < n; i++)
	{
		result[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			result[i][j] = matrix[i][j + n];
		}
	}
	return result;
}

double *solution(double **matrix, int rows, int columns)
{
	int last_columns_index = columns - 1;
	double *result = (double *)malloc(rows * sizeof(double));
	for (int row = 0; row < rows; row++)
		result[row] = matrix[row][last_columns_index] / matrix[row][row];
	return result;
}

double **n_coefficients(int n)
{
	int r_rows = n, r_columns = n + 1;
	double **result = (double **)malloc(r_rows * sizeof(double *));
	for (int i = 0; i < r_rows; i++)
	{
		result[i] = (double *)malloc(r_columns * sizeof(double));
		double x, y;
		char *string = to_string(i);

		char x_string[100];
		strcpy(x_string, "Enter X");
		strcat(x_string, string);
		strcat(x_string, " : ");
		get_double(x_string, &x);

		char y_string[100];
		strcpy(y_string, "Enter Y");
		strcat(y_string, string);
		strcat(y_string, " : ");
		get_double(y_string, &y);
		free(string);
		string = NULL;

		for (int j = 0; j < r_rows; j++)
		{
			result[i][j] = pow(x, j);
		}
		result[i][r_columns - 1] = y;
	}
	gauss_jordon_elimination(result, r_rows, r_columns);
	return result;
}

double det(double **matrix, int rows, int columns)
{
    if (rows == 1 && columns == 1)
    {
        return matrix[0][0];
    }
    double sum = 0;
    double **submatrix = (double **)malloc((rows - 1) * sizeof(double *));
    for (int i = 0; i < rows - 1; i++) submatrix[i] = (double *)malloc((columns - 1) * sizeof(double));
    for (int k = 0; k < columns; k++)
    {
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = 0; j < columns - 1; j++)
            {
                if (i < k)
                    submatrix[j][i] = matrix[j + 1][i];
                else
                    submatrix[j][i] = matrix[j + 1][i + 1];
            }
        }
        sum += matrix[0][k]*pow(-1, 0 + k)*det(submatrix, rows - 1, columns - 1);
    }
    for (int i = 0; i < rows - 1; i++)
    {
        free(submatrix[i]);
    }
    free(submatrix);
    return sum;
}

int main()
{
	int rows, columns;
	printf("Enter number of rows: ");
	scanf("%d", &rows);
	printf("Enter number of columns: ");
	scanf("%d", &columns);

	double **matrix = (double **)malloc(rows * sizeof(double *));
	for (int row = 0; row < rows; row++)
	{
		matrix[row] = (double *)malloc(columns * sizeof(double));
		printf("Enter row number %d: ", row + 1);
		for (int column = 0; column < columns; column++)
			scanf("%lf", &matrix[row][column]);
	}
	show_matrix(matrix, rows, columns);

	gauss_elimination(matrix, rows, columns);
	printf("Matrix after gauess elimination:\n");
	show_matrix(matrix, rows, columns);

	gauss_jordon_elimination(matrix, rows, columns);
	printf("Matrix after gauess-jordon elimination:\n");
	show_matrix(matrix, rows, columns);

	double **inverse = get_inverse(matrix, rows);
	printf("Matrix Inverse:\n");
	show_matrix(inverse, rows, rows);
	for (int i = 0; i < rows; i++)
		free(inverse[i]);
	free(inverse);


	
	// long int numberOfcoefficients;
	// get_integer("Enter Number of Coefficients : ", &numberOfcoefficients);
	// double **system_matrix = (double **)calloc(numberOfcoefficients, sizeof(double));
	// system_matrix = n_coefficients(numberOfcoefficients);
	// show_matrix(system_matrix, numberOfcoefficients, numberOfcoefficients+1);
	// for (int i = 0; i < numberOfcoefficients; i++)
	// 	free(system_matrix[i]);
	// free(system_matrix);




	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
}
