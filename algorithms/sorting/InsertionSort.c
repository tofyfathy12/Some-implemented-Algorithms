#include <stdio.h>

void print_arr(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* i, int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

void sort(int* arr, int length) {
    for (int i = 1; i < length; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key;
        print_arr(arr, length);
    }
}


int main() {
    int len = 6;
    int arr[] = {8, 2, 4, 9 ,3, 6};
    
    print_arr(arr, len);
    printf("===============================\n");
    sort(arr, len);
    printf("===============================\n");
    print_arr(arr, len);

    return 0;
}