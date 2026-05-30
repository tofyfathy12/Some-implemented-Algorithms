#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Heap {
    int *arr;
    int capacity;
    int heapsize;
} Heap;


Heap *construct_heap(int capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    
    heap->arr = (int *)malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->heapsize = 0;

    return heap;
}

void destroy_heap(Heap *heap) {
    free(heap->arr);
    free(heap);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool is_empty(Heap *heap) {
    return (heap->heapsize == 0);
}

void heapify_up(Heap *heap, int index) {
    if (index < 0 || index >= heap->heapsize) {
        printf("Error: Index %d is out of bounds: [%d, %d[\nLine: %d", index, 0, heap->heapsize, __LINE__);
        destroy_heap(heap);
        exit(1);
    }

    int parent_idx = ((index + 1) / 2) - 1;

    while (parent_idx >= 0 && heap->arr[index] < heap->arr[parent_idx]) {
        swap(heap->arr + index, heap->arr + parent_idx);
        index = parent_idx;
        parent_idx = ((index + 1) / 2) - 1;
    }
}

void heapify_down(Heap *heap, int index) {
    if (index < 0 || index >= heap->heapsize) {
        printf("Error: Index %d is out of bounds: [%d, %d[\nLine: %d", index, 0, heap->heapsize, __LINE__);
        destroy_heap(heap);
        exit(1);
    }

    int smallest_idx = index;
    do
    {
        int l = 2 * (index + 1) - 1;
        int r = 2 * (index + 1);
        if (l < heap->heapsize && heap->arr[l] < heap->arr[index])
            smallest_idx = l;
        if (r < heap->heapsize && heap->arr[r] < heap->arr[smallest_idx])
            smallest_idx = r;

        if (smallest_idx == index)
            break;    
        swap(heap->arr + index, heap->arr + smallest_idx);
        index = smallest_idx;
    } while (true);
}

void heap_insert(Heap *heap, int num) {
    if (heap->heapsize == heap->capacity) {
        printf("Error: Cannot insert to a full Heap !!");
        destroy_heap(heap);
        exit(1);
    }

    heap->arr[heap->heapsize] = num;
    heapify_up(heap, heap->heapsize);
    heap->heapsize++;
}

int extract_min(Heap *heap) {
    if (heap->heapsize == 0) {
        printf("Error: Cannot extract_min from an empty heap !!");
        destroy_heap(heap);
        exit(1);
    }

    swap(heap->arr + 0, heap->arr + heap->heapsize - 1);
    heap->heapsize--;

    if (heap->heapsize > 0)
        heapify_down(heap, 0);

    return heap->arr[heap->heapsize];
}

Heap *build_min_heap(int *arr, int len) {
    Heap *heap = construct_heap((len << 1));
    heap->arr = arr;
    heap->heapsize = len;

    int last_parent_idx = ((len + 1) >> 1) - 1;
    for (int i = last_parent_idx; i >= 0; i--)
        heapify_down(heap, i);

    return heap;
}

int *heap_sort(int *arr, int len) {

    int *res = (int *)malloc(len * sizeof(int));

    Heap *heap = build_min_heap(arr, len);

    int res_idx = 0;
    while (!is_empty(heap)) {
        res[res_idx++] = extract_min(heap);
    }

    // destroy_heap(heap);
    free(heap);
    return res;
}

void print_arr(int *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    int n = 9;
    int arr[] = {5, 2, 4, 8, 2, 9, 10, 2, 3};

    int *sorted_arr = heap_sort(arr, n);

    printf("Arr: ");
    print_arr(arr, n);

    printf("Sorted Arr: ");
    print_arr(sorted_arr, n);

    free(sorted_arr);
}