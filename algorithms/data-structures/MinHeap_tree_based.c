#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "Queue.h"

#define MIN_GAP 4

typedef struct TreeNode {
    struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
    int val;
    
    int width;
    int subtree_width;
    int center_offset;
    int absolute_center;
    int start;
} TreeNode;

typedef struct Heap {
    TreeNode *root;
    int heapsize;
} Heap;

void print_queue(Queue *queue) {
    for (int i = 0; i < queue->size; i++) {
        TreeNode *node = (TreeNode *) queue->dequeue(queue);
        printf("%d ", node->val);
        queue->enqueue(queue, node);
    }
    printf("\n");
}

Queue *construct_myqueue() {
    Queue *q = construct_queue();
    q->print = print_queue;
    
    return q;
}

TreeNode *create_treenode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->val = val;

    node->width = (val != 0) ? log10(abs(val)) + 1 + (val < 0) : 1;
    node->subtree_width = 0;
    node->center_offset = 0;
    node->absolute_center = 0;
    node->start = 0;

    return node;
}

Heap *construct_heap() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));

    heap->root = NULL;
    heap->heapsize = 0;

    return heap;
}

void destroy_tree(TreeNode *root) {
    if (root->left != NULL)
        destroy_tree(root->left);
    if (root->right != NULL)
        destroy_tree(root->right);
    free(root);
}

void destroy_heap(Heap *heap) {
    if (heap->root != NULL)
        destroy_tree(heap->root);
    free(heap);
}

bool is_empty(Heap *heap) {
    return (heap->heapsize == 0);
}

TreeNode *get_node_by_index(Heap *heap, int index) {
    TreeNode *node = heap->root;
    int directions_num = index + 1;
    if (index > 0) {
        int dir_len = log2(directions_num);
        bool directions[dir_len];
        int dir_idx = dir_len - 1;
        while (directions_num > 1) {
            directions[dir_idx--] = (directions_num & 1);
            directions_num >>= 1;
        }
        for (int i = 0; i < dir_len; i++) {
            if (directions[i])
                node = node->right;
            else
                node = node->left;
        }
    }

    return node;
}

void swap_nodes(TreeNode *node1, TreeNode *node2) {
    int tmp_val = node1->val;
    int tmp_width = node1->width;
    int tmp_center_off = node1->center_offset;
    int tmp_abs_center = node1->absolute_center;
    int tmp_start = node1->start;
    int tmp_subtree_width = node1->subtree_width;
    
    node1->val = node2->val;
    node1->width = node2->width;
    node1->center_offset = node2->center_offset;
    node1->absolute_center = node2->absolute_center;
    node1->start = node2->start;
    node1->subtree_width = node2->subtree_width;

    node2->val = tmp_val;
    node2->width = tmp_width;
    node2->center_offset = tmp_center_off;
    node2->absolute_center = tmp_abs_center;
    node2->start = tmp_start;
    node2->subtree_width = tmp_subtree_width;
}

void heapify_up_by_index(Heap *heap, int index) {
    if (index < 0 || index >= heap->heapsize) {
        printf("Error: Index %d is out of bounds: [%d, %d[\nLine: %d", index, 0, heap->heapsize, __LINE__);
        destroy_heap(heap);
        exit(1);
    }

    TreeNode *node = get_node_by_index(heap, index);
    while (node->parent != NULL && node->val < node->parent->val) {
        swap_nodes(node, node->parent);
        node = node->parent;
    }
}

void heapify_down_by_index(Heap *heap, int index) {
    if (index < 0 || index >= heap->heapsize) {
        printf("Error: Index %d is out of bounds: [%d, %d[\nLine: %d", index, 0, heap->heapsize, __LINE__);
        destroy_heap(heap);
        exit(1);
    }

    TreeNode *node = get_node_by_index(heap, index);
    do
    {
        TreeNode *smallest = node;
        if (node->left != NULL && node->left->val < smallest->val)
            smallest = node->left;
        if (node->right != NULL && node->right->val < smallest->val)
            smallest = node->right;

        if (smallest == node) break;

        swap_nodes(node, smallest);
        node = smallest;
    } while (true);
}

void heapify_up_by_node(Heap *heap, TreeNode *node) {
    while (node != heap->root && node->val < node->parent->val) {
        swap_nodes(node, node->parent);
        node = node->parent;
    }
}

void heapify_down_by_node(Heap *heap, TreeNode *node) {
    do
    {
        TreeNode *smallest = node;
        if (node->left != NULL && node->left->val < smallest->val)
            smallest = node->left;
        if (node->right != NULL && node->right->val < smallest->val)
            smallest = node->right;

        if (smallest == node) break;

        swap_nodes(node, smallest);
        node = smallest;
    } while (true);
}

void heap_insert(Heap *heap, int val) {
    TreeNode *newNode = create_treenode(val);
    if (heap->heapsize > 0) {
        TreeNode *node = heap->root;
        int directions_num = heap->heapsize + 1;
        int dir_len = log2(directions_num);
        bool directions[dir_len];
        int dir_idx = dir_len - 1;
        while (directions_num > 1) {
            directions[dir_idx--] = (directions_num & 1);
            directions_num >>= 1;
        }
        for (int i = 0; i < dir_len - 1; i++) {
            if (directions[i])
                node = node->right;
            else
                node = node->left;
        }
        if (directions[dir_len - 1])
            node->right = newNode;
        else
            node->left = newNode;
        newNode->parent = node;
    }
    else {
        heap->root = newNode;
    }
    heap->heapsize++;

    heapify_up_by_node(heap, newNode);
}

int extract_min(Heap *heap) {
    if (heap->heapsize == 0) {
        printf("Error: Cannot extract_min from an empty heap !!");
        destroy_heap(heap);
        exit(1);
    }

    TreeNode *last = get_node_by_index(heap, heap->heapsize - 1);

    int val = heap->root->val;

    if (heap->heapsize == 1) {
        free(heap->root);
        heap->root = NULL;
        heap->heapsize = 0;
        return val;
    }

    if (last->parent->left == last)
        last->parent->left = NULL;
    else if (last->parent->right == last)
        last->parent->right = NULL;

    heap->root->val = last->val;
    free(last);
    heap->heapsize--;

    heapify_down_by_node(heap, heap->root);

    return val;
}

Heap *build_min_heap(int *arr, int len) {
    Heap *heap = construct_heap();

    for (int i = 0; i < len; i++) {
        heap_insert(heap, arr[i]);
    }

    return heap;
}

int *heap_sort(int *arr, int len) {

    int *res = (int *)malloc(len * sizeof(int));

    Heap *heap = build_min_heap(arr, len);

    int res_idx = 0;
    while (!is_empty(heap)) {
        res[res_idx++] = extract_min(heap);
    }

    destroy_heap(heap);
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

long long mypow(long long base, long long power) {
    long long result = 1;
    while (power > 0) {
        if ((power & 1) == 0) {
            base *= base;
            power >>= 1;
        }
        else {
            result *= base;
            power--;
        }
    }
    return result;
}

TreeNode ***get_heap_levels(Heap *heap) {
    int levels_num = log2(heap->heapsize) + 1;
    TreeNode ***levels = (TreeNode ***)malloc((levels_num + 1) * sizeof(TreeNode **));
    int levels_idx = 0;

    Queue *q = construct_queue();
    q->enqueue(q, heap->root);

    int level_size = 1;
    TreeNode **level = (TreeNode **)malloc((level_size + 1) * sizeof(TreeNode *));
    for (int i = 0; i < level_size + 1; i++) level[i] = NULL;
    int cur_level_idx = 0;

    while (!isEmpty(q)) {
        if (cur_level_idx == level_size) {
            cur_level_idx = 0;
            levels[levels_idx++] = level;
            level_size *= 2;
            level = (TreeNode **)malloc((level_size + 1) * sizeof(TreeNode *));
            for (int i = 0; i < level_size + 1; i++) level[i] = NULL;
        }

        TreeNode *node = (TreeNode *) q->dequeue(q);
        level[cur_level_idx++] = node;

        if (node->left != NULL)
            q->enqueue(q, node->left);
        if (node->right != NULL)
            q->enqueue(q, node->right);
    }
    levels[levels_idx++] = level;
    levels[levels_idx] = NULL;

    destory_queue(q);
    return levels;
}

void print_heap_levels(Heap *heap) {
    TreeNode ***levels = get_heap_levels(heap);

    int levels_idx = 0;
    while (levels[levels_idx] != NULL) {
        printf("Level %d:\n", levels_idx + 1);
        int level_idx = 0;
        while (levels[levels_idx][level_idx] != NULL) {
            printf("%d ", levels[levels_idx][level_idx]->val);
            level_idx++;
        }
        printf("\n");
        free(levels[levels_idx]);
        levels_idx++;
    }
    free(levels);
}

void print_heap_as_array(Heap *heap) {
    for (int i = 0; i < heap->heapsize; i++) {
        TreeNode *node = get_node_by_index(heap, i);
        printf("%d ", node->val);
    }
    printf("\n");
}

char *sprint_multiple(char *dst, char c, int times) {
    for (int i = 0; i < times; i++) {
        dst[i] = c;
    }
    dst[times] = '\0';
    return dst + times;
}

char *sprint_num(char *dst, TreeNode *node) { // assumes you handle null-terminators yourself
    int length = node->width;
    int num = node->val;
    for (int i = length - 1; i >= 0; i--) {
        int digit = num % 10;
        dst[i] = digit + '0';
        num /= 10;
    }
    if (node->val < 0) dst[0] = '-';
    return dst + length;
}

//              2           --> root center = absolute_center; start = center - width/2
//             / \          --> slashes are drawn one per row until child center
//            /   \         --> left slash writes at node->start - i - 1
//           /     \        --> right slash writes at node->start + i + 1
//          /       \       --> distance = abs(parent_center - child_center)
//         /         \      --> lines_num adds max(left_distance, right_distance)
//        3           4     --> child centers = parent_center +/- child->center_offset
//       / \         / \    --> center_offset comes from left_width + MIN_GAP/2
//      /   \       /   \   --> subtree_width = max(node width, left + MIN_GAP + right)
//     8     5     9     10 --> screen width = root->subtree_width; values printed at start

void debug_screen(int lines_num, int line_size, char screen[lines_num][line_size]) {
    for (int i = 0; i < lines_num; i++) {
        for (int j = 0; j < line_size; j++) {
            char c = screen[i][j];
            switch (c) {
                case ' ':
                    printf("_");
                    break;
                case '\0':
                    printf("\\0");
                    break;
                default:
                    printf("%c", c);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void calculate_subtree_widths(TreeNode *root) {
    int left_width = 0, right_width = 0;
    if (root->left != NULL) {
        calculate_subtree_widths(root->left);
        left_width = root->left->subtree_width;
    }
    if (root->right != NULL) {
        calculate_subtree_widths(root->right);
        right_width = root->right->subtree_width;
    }
    root->subtree_width = max(root->width, left_width + MIN_GAP + right_width);
    root->center_offset = left_width + MIN_GAP/2;
    root->absolute_center = root->center_offset;
}

void calculate_abs_centers(TreeNode *root) {
    root->start = root->absolute_center - root->width/2;
    if (root->left != NULL) {
        root->left->absolute_center = root->absolute_center - root->left->center_offset;
        calculate_abs_centers(root->left);
    }
    if (root->right != NULL) {
        root->right->absolute_center = root->absolute_center + root->right->center_offset;
        calculate_abs_centers(root->right);
    }
}

void print_heap_as_tree(Heap *heap) {
    int levels_num = log2(heap->heapsize) + 1;
    TreeNode ***levels = get_heap_levels(heap);
    
    calculate_subtree_widths(heap->root);
    calculate_abs_centers(heap->root);

    int lines_num = levels_num;
    for (int i = 0; i < levels_num - 1; i++) {
        TreeNode **lvl1 = levels[i];
        TreeNode **lvl2 = levels[i + 1];
        
        for (int j = 0; lvl1[j] != NULL; j++) {
            TreeNode *node = lvl1[j];
            
            TreeNode *left = lvl2[j*2];
            TreeNode *right = lvl2[j*2 + 1];

            int left_distance = 0, right_distance = 0;
            if (left != NULL) left_distance = abs(node->absolute_center - left->absolute_center);
            if (right != NULL) right_distance = abs(node->absolute_center - right->absolute_center);

            lines_num += max(left_distance, right_distance);
        }
    }

    char screen[lines_num][heap->root->subtree_width + 1];
    memset(screen, ' ', lines_num * (heap->root->subtree_width + 1) * sizeof(char));
    for (int i = 0; i < lines_num; i++)
        screen[i][heap->root->subtree_width] = '\0';

    int levels_idx = 0, lines_idx = 0;
    while (levels[levels_idx] != NULL) {
        char *next_dst = screen[lines_idx];

        int left_distance = 0, right_distance = 0;
        int level_idx = 0;
        while (levels[levels_idx][level_idx] != NULL) {
            TreeNode *node = levels[levels_idx][level_idx];
            sprint_num(next_dst + node->start, node);

            if (levels[levels_idx + 1] != NULL) {
                TreeNode *left = levels[levels_idx + 1][level_idx*2];
                TreeNode *right = levels[levels_idx + 1][level_idx*2 + 1];

                int new_left_distance = 0;
                int new_right_distance = 0;
                if (left != NULL) {
                    new_left_distance = abs(node->absolute_center - left->absolute_center);
                    for (int i = 0; i < new_left_distance; i++) {
                        char *wrt = screen[lines_idx + i + 1];
                        wrt[node->start - i - 1] = '/';
                    }
                }
                if (right != NULL) {
                    new_right_distance = abs(node->absolute_center - right->absolute_center);
                    for (int i = 0; i < new_right_distance; i++) {
                        char *wrt = screen[lines_idx + i + 1];
                        wrt[node->start + i + 1] = '\\';
                    }
                }
                left_distance = max(left_distance, new_left_distance);
                right_distance = max(right_distance, new_right_distance);
            }
            level_idx++;
        }
        lines_idx += max(left_distance, right_distance) + 1;
        next_dst = screen[lines_idx];
        levels_idx++;
    }

    levels_idx = 0;
    while (levels[levels_idx] != NULL) {
        free(levels[levels_idx]);
        levels_idx++;
    }
    free(levels);

    for (int i = 0; i < lines_num; i++) printf("%s\n", screen[i]);
}

int main() {
    int n = 13;
    int arr[] = {5, 2, 4, 8, 9, 10, 3, 200, 18, 2000, 6, 19, 28};

    int *sorted_arr = heap_sort(arr, n);

    printf("Arr: ");
    print_arr(arr, n);

    printf("Sorted Arr: ");
    print_arr(sorted_arr, n);

    free(sorted_arr);

    Heap *heap = build_min_heap(arr, n);

    printf("Heap as array: ");
    print_heap_as_array(heap);

    printf("Heap as levels:\n");
    print_heap_levels(heap);

    printf("Heap as tree:\n");
    print_heap_as_tree(heap);

    destroy_heap(heap);
}