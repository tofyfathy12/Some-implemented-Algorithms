#include <stdio.h>
#include <stdlib.h>

struct array
{
    int *arr;
    int size;
};

void display_array(struct array A)
{
    printf("{");
    for (int i = 0; i < A.size; i++) if (i < A.size-1) printf("%d, ", A.arr[i]);
    printf("%d}", A.arr[A.size-1]);
}

// void flip(int *arr, int start, int end)
// {
//     for (int i = start; i <= end; i++) arr[i] = 1 - arr[i];
// }

// int ones_num(int *arr, int start, int end)
// {
//     int count = 0;
//     for (int i = start; i <= end; i++) if (arr[i] == 1) count ++;
//     return count;
// }
// int flip_ones_num(int *arr, int start, int end)
// {
//     flip(arr, start, end);
//     return ones_num(arr, start, end);
// }

struct array kandane(int *A, int size)
{
    struct array subarr;
    subarr.size = 1;
    subarr.arr = (int *)malloc(subarr.size*sizeof(int));
    subarr.arr[0] = A[0];
    int max_current = A[0];
    int max_global = max_current;
    for (int i = 1; i < size; i++)
    {
        if (A[i] > A[i] + max_current)
        {
            max_current = A[i];
            if (max_current > max_global) max_global = max_current;
            subarr.size = 1;
            subarr.arr = (int *)realloc(subarr.arr, subarr.size*sizeof(int));
            subarr.arr[subarr.size - 1] = A[i];
        }
        else
        {
            max_current += A[i];
            if (max_current > max_global)
            {
                max_global = max_current;
                subarr.size ++;
                subarr.arr = (int *)realloc(subarr.arr, subarr.size*sizeof(int));
                subarr.arr[subarr.size-1] = A[i];
            }
        }
    }
    return subarr;
}

int main()
{
    int arr1[5] = {1, -3, 2, 1, -1};
    struct array subarr1 = kandane(arr1, 5);
    display_array(subarr1);
}