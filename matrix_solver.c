#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define EPSILON 1e-9

char *to_string(int num)
{
	int digits_num = 0;
	if (num == 0) digits_num = 1;
	else
	{
		int temp = num;
		while (temp > 0)
		{
			temp /= 10;
			digits_num ++;
		}
	}
	char *string = (char *)calloc(digits_num + 1, sizeof(char));
	string[digits_num] = '\0';
	for (int i = digits_num - 1; i >= 0; i--)
	{
		string[i] = (num%10) + 48;
		num --;
	}
	return string;
}

void delete_buffer()
{
	char garbage[1000];
	scanf("%[^\n]%*c", &garbage);
}
double get_double(char *str, double *n)
{
    bool valid = false;
    while (!valid)
    {
        printf("%s", str);
        char newline_check;
        int checker = scanf("%lf%c", n, &newline_check);
        if (checker != 2 || newline_check != '\n')
        {
            delete_buffer();
            printf("THAT'S NOT VALID. TRY AGAIN.\n");
        }
        else valid = true;
    }
    return *n;
}

int get_integer(char *str, int *n)
{
    bool valid = false;
    while (!valid)
    {
        printf("%s", str);
        char newline_check;
        int checker = scanf("%d%c", n, &newline_check);
        if (checker != 2 || newline_check != '\n')
        {
            delete_buffer();
            printf("THAT'S NOT VALID. TRY AGAIN.\n");
        }
        else valid = true;
    }
    return *n;
}

void show_matrix(double *matrix, int rows, int columns)
{
	
	for (int row = 0; row < rows; row ++)
	{
		printf("==========================================\n|");
		for (int column = 0; column < columns; column ++)
		{
			double num = matrix[row*columns + column];
			printf("%.4lf ", num);
			printf("| ");
		}
		printf("\n");
	}
	printf("==========================================\n");
}


double *transpose(double *matrix, int rows, int columns)
{
	double *new_matrix = malloc(columns*rows*sizeof(double));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			new_matrix[j*rows + i] = matrix[i*columns + j];
		}
	}
	return new_matrix;
}
void gauss_elimination(double *matrix, int rows, int columns)
{
	int number_of_operations = rows-1;
	for (int operation = 0; operation < number_of_operations; operation ++)
	{
		int starting_column = operation;
		int non_zero_pivot_row = -1;
		// finding the non zero pivot row
		while (non_zero_pivot_row == -1 &&  starting_column < columns)
		{
			for (int row = operation; row < rows; row++) // changed according to operation
			{
				if( matrix[row*columns + starting_column] != 0 ) // changed according to operation
				{
					non_zero_pivot_row = row;
					break;
				}
			}
			if (non_zero_pivot_row == -1) starting_column ++;
			else break;
		}
		// exchange row 0 with non zero pivot row thus element 0 with 3 and 1 with 4 and 2 with 5 ie the number of columns
		if (matrix[operation * columns + starting_column] == 0 && non_zero_pivot_row != -1) // changed according to operation
		{
			for (int column = starting_column; column < columns; column++) // changed according to operation
			{
				double temp = matrix[operation * columns + column];
				matrix[operation * columns + column] = matrix[non_zero_pivot_row*columns + column];
				matrix[non_zero_pivot_row*columns + column] = temp;
			}
		}
		for (int row = operation + 1; row < rows; row++) // changed according to operation
		{
			double subtracted_num = 0;
			double multiplied_num = matrix[row*columns + starting_column] / matrix[operation * columns + starting_column]; // changed according to operation
			for (int column = 0; column < columns; column++)
			{
				int element_index = row*columns + column;
				subtracted_num = matrix[operation * columns + column] * multiplied_num;
				matrix[element_index] -= subtracted_num;
				if (fabs(matrix[element_index]) < 1e-9) matrix[element_index] = 0;
			}
		}
	}
}

int gauss_jordon_elimination(double *matrix, int rows, int columns)
{
	gauss_elimination(matrix, rows, columns);
	int num_of_operations = rows;
	for (int operation = 1; operation < num_of_operations; operation++)
	{
		int pivot_row = rows-operation;
		int pivot_column = 0;
		bool found = false;
		for (int row = rows-operation; row >= 0; row--)
		{
			for (int column = 0; column < columns; column++)
			{
				if (!(matrix[row*columns + column] == 0))
				{
					pivot_row = row;
					pivot_column = column;
					found = true;
					break;
				}
			}
			if (found) break;
		}
		int pivot_index = pivot_row*columns + pivot_column;
		for (int row = pivot_row-1; row >= 0; row--) // changed according to operation
		{
			double multiplied_num = matrix[row*columns + pivot_column]/matrix[pivot_index];
			double subtracted_num = 0;
			for (int column = columns - 1; column >= 0; column--)
			{
				subtracted_num = multiplied_num*matrix[pivot_row*columns + column];
				matrix[row*columns + column] -= subtracted_num;
				if (fabs(matrix[row*columns + column]) < -1e-9) matrix[row*columns + column] = 0;
			}
		}
	}
}

double *solution(double *matrix, int rows, int columns)
{
	int last_columns_index = columns-1;
	double *result = malloc(rows*sizeof(double));
	for (int row = 0; row < rows; row++)
	{
		result[row] = matrix[row*columns + last_columns_index]/matrix[row*columns + row];
	}
	return result;
}

double *n_coefficients(int n)
{
	int r_rows = n, r_columns = n + 1;
	double *result = calloc(r_rows*r_columns, sizeof(double));
	for (int i = 0; i < r_rows; i++)
	{
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

		for (int j = 0; j < r_rows; j++)
		{
			result[i*r_columns + j] = pow(x, j);
		}
		result[i*r_columns + r_columns - 1] = y;
	}
	gauss_jordon_elimination(result, r_rows, r_columns);
	return result;
}


char newline;
int checker;
int main()
{
	int rows, columns;
	printf("Enter number of rows: ");
	scanf("%d", &rows);
	printf("Enter number of columns: ");
	scanf("%d", &columns);
	
	double matrix[rows][columns];
	for (int row = 0; row < rows; row++)
	{
		printf("Enter row number %d: ", row+1);
		for (int column = 0; column < columns; column++) scanf("%lf", &matrix[row][column]);
	}
	show_matrix(*matrix, rows, columns);

	gauss_elimination(*matrix, rows, columns);
	printf("Matrix after gauess elimination:\n");
	show_matrix(*matrix, rows, columns);

	gauss_jordon_elimination(*matrix, rows, columns);
	printf("Matrix after gauess-jordon elimination:\n");
	show_matrix(*matrix, rows, columns);
	// int numberOfcoefficients;
	// get_integer("Enter Number of Coefficients : ", &numberOfcoefficients);
	// double *system_matrix = (double *)calloc(numberOfcoefficients, sizeof(double));
	// system_matrix = n_coefficients(numberOfcoefficients);
	// show_matrix(system_matrix, numberOfcoefficients, numberOfcoefficients+1);
}
