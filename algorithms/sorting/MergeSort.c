#include <stdio.h>

void print_arr(int* arr, int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge_sorted(int* arr, int start1, int end1, int start2, int end2) {
    int len1 = end1 - start1, len2 = end2 - start2;
    int new_len = len1 + len2;

    int temp_arr[new_len];
    int i = start1, j = start2;

    int start = (start1 < start2) ? start1 : start2;
    int end = (end1 > end2) ? end1 : end2;

    int index = 0;
    while (i < end1 && j < end2) {
        if (arr[i] < arr[j]) {
            temp_arr[index++] = arr[i++];
        }
        else {
            temp_arr[index++] = arr[j++];
        } 
    }

    while (i < end1) {
        temp_arr[index++] = arr[i++];
    }
    while (j < end2) {
        temp_arr[index++] = arr[j++];
    }
    
    for (int i = start; i < end; i++) {
        arr[i] = temp_arr[i - start];
    }
}

void sort(int* arr, int start, int end) {
    //len = 6
    // start = 0, end = 6
    int len = end - start;
    if (len == 1)
        return;

    int mid = start + (end - start)/2;
    int left_start = start, left_end = mid;
    int right_start = mid, right_end = end;

    print_arr(arr, left_start, left_end); // debugging

    sort(arr, left_start, left_end);

    print_arr(arr, left_start, left_end); // debugging
    printf("****************************\n"); // debugging
    print_arr(arr, right_start, right_end); // debugging

    sort(arr, right_start, right_end);

    print_arr(arr, right_start, right_end); // debugging

    merge_sorted(arr, left_start, left_end, right_start, right_end);
    
}

int main() {
    int len = 6;
    int arr[] = {8, 2, 4, 9 ,3, 6};
    
    print_arr(arr, 0, len);
    printf("===============================\n");
    sort(arr, 0, len);
    // merge_sorted(arr, 4, 6, 1, 4);
    printf("===============================\n");
    print_arr(arr, 0, len);

    return 0;
}