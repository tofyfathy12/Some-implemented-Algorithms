#include <stdio.h>
#include <stdlib.h>


void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



int *add_arr(int arr1[], int size1, int arr2[], int size2)
{
    int total_size = size1 + size2;
    int *total_arr = (int *)malloc(total_size*sizeof(int));
    for (int i = 0; i < size1; i++) total_arr[i] = arr1[i];
    for (int i = size1; i < total_size; i++) total_arr[i] = arr2[i-size1];
    return total_arr;
}


int get_pivot_index(int *arr, int first_index, int last_index)
{
    int num1 = arr[first_index];
    int mid_index = (first_index + last_index)/2;
    int num2 = arr[mid_index];
    int num3 = arr[last_index];
    if (num1 >= num2 && num1 >= num3) return (num2 > num3) ? mid_index : last_index;
    else if (num2 >= num1 && num2 >= num3) return (num1 > num3) ? first_index : last_index;
    else if (num3 >= num1 && num3 >= num2) return (num1 > num2) ? first_index : mid_index;
}

void quick_sort(int *arr, int first_index, int last_index)
{
    int size = last_index - first_index + 1;
    if (size > 1)
    {
        int pivot_index = get_pivot_index(arr, first_index, last_index);
        swap(&arr[pivot_index], &arr[last_index]);
        pivot_index = last_index;

        int large_left_index = first_index;
        int small_right_index = last_index-1;

        while (large_left_index <= small_right_index)
        {
            while (large_left_index < last_index)
            {
                if (arr[large_left_index] > arr[pivot_index]) break;
                else large_left_index ++;
            }
            while (small_right_index > first_index)
            {
                if (arr[small_right_index] < arr[pivot_index]) break;
                else small_right_index --;
            }
            if (large_left_index >= small_right_index) break;
            else
            {
                swap(&arr[large_left_index], &arr[small_right_index]);
                large_left_index ++;
                small_right_index --;
            }
        }

        swap(&arr[large_left_index], &arr[pivot_index]);
        pivot_index = large_left_index;
        if (pivot_index > first_index)
        {
            int left_first_index = first_index;
            int left_last_index = pivot_index - 1;
            quick_sort(arr, left_first_index, left_last_index);
        }
        if (pivot_index < last_index)
        {
            int right_first_index = pivot_index + 1;
            int right_last_index = last_index;
            quick_sort(arr, right_first_index, right_last_index);
        }
    }
}


int main()
{
    const int size = 8;
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    quick_sort(arr, 0, size-1);
    print_array(arr, size);
}
