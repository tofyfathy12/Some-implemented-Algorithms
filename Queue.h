#include <stdio.h>
#include <stdlib.h>

#define False 0
#define True 1
typedef unsigned char boolean;

typedef struct nd {
    void* data;
    struct nd* next;
} Node;


typedef struct qu {
    Node* head;
    Node* tail;
    void (*enqueue)(struct qu* self, void* data);
    void* (*dequeue)(struct qu* self);
    void* (*front)(struct qu* self);
    boolean (*isEmpty)(struct qu* self);
    void (*print)(struct qu* self);
    size_t size;
} Queue;

void destory_queue(Queue* q);
Queue* contrust_queue();
void print_int_queue(Queue* self);
void enqueue(Queue* self, void* data);
void* dequeue(Queue* self);
void* front(Queue* self);
boolean isEmpty(Queue* self);
Node* construct_node(void* data);

// int main(int argc, char* argv[]) {
//     Queue* myq = contrust_queue();
//     myq->print = print_int_queue;
//     for (int i = 1; i <= 10; i++) {
//         int* num = (int*)malloc(sizeof(int));
//         *num = i;
//         myq->enqueue(myq, num);
//     }
//     myq->print(myq);
//     destory_queue(myq);
// }

void destory_queue(Queue* q) {
    Node* prev = NULL;
    for (Node* iter = q->head; iter != NULL; iter = iter->next) {
        free(iter->data);
        if (prev != NULL) {
            free(prev);
        }
        prev = iter;
    }
    free(prev);
    free(q);
}

Queue* contrust_queue() {
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));

    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->size = 0;
    new_queue->enqueue = enqueue;
    new_queue->dequeue = dequeue;
    new_queue->front = front;
    new_queue->isEmpty = isEmpty;

    return new_queue;
}

void print_int_queue(Queue* self) {
    printf("[");
    for (Node* iter = self->head; iter != NULL; iter = iter->next) {
        printf("%d", *(int*)iter->data);
        if (iter->next != NULL)
            printf(", ");
    }
    printf("]\n");
}

void enqueue(Queue* self, void* data) { //add to tail and advance tail pointer
    Node* new_node = construct_node(data);
    if (self->isEmpty(self)) {
        self->head = new_node;
        self->tail = new_node;
    }
    else {
        self->tail->next = new_node;
        self->tail = new_node;
    }
    self->size++;
}

void* dequeue(Queue* self) { //remove from head and advance head pointer
    if (self->isEmpty(self)) {
        printf("Error: Can't use dequeue() on Empty Queue\n");
    }
    Node* removed_node = self->head;
    self->head = self->head->next;
    if (self->head == NULL) {
        self->tail = NULL;
    }
    self->size--;
    void* returned_data = removed_node->data;
    free(removed_node);
    return returned_data;
}

void* front(Queue* self) { //look at the item to be removed next
    if (self->isEmpty(self)) {
        printf("Error: Can't use front() on Empty Queue\n");
    }
    return self->head->data;
}

boolean isEmpty(Queue* self) {
    return (self->size == 0);
}

Node* construct_node(void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

