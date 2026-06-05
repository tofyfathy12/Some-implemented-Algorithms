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
    printf("%d}\n", A.arr[A.size-1]);
}

struct array kandane(int *A, int size, int *max_sum)
{
    struct array subarr;
    subarr.arr = (int *)malloc(size*sizeof(int));
    subarr.size = 1;
    subarr.arr[0] = A[0];

    int max_current = A[0];
    *max_sum = max_current;
    for (int i = 1; i < size; i++) {
        if (max_current < 0) {
            max_current = A[i];
            subarr.size = 0;
        }
        else {
            max_current += A[i];
        }
        
        subarr.arr[subarr.size++] = A[i];
        if (max_current > *max_sum) {
            *max_sum = max_current;
        }
    }

    subarr.arr = (int *)realloc(subarr.arr, subarr.size * sizeof(int));
    return subarr;
}

int main()
{
    int arr[] = {2, 3, -8, 7, -1, 2, 3};
    int n = sizeof(arr) / sizeof(int);
    
    int max_sum;
    struct array subarr = kandane(arr, n, &max_sum);

    printf("subarray of maximum sum = ");
    display_array(subarr);
    printf("sum of subarray = %d\n", max_sum);
}