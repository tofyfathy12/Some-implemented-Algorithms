#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertNode(int value, Node *head)
{
    Node *last_node = head;
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    last_node->next = createNode(value);
}

void printList(Node *start)
{
    Node *nextnode = start;
    while (nextnode->next != NULL)
    {
        printf("%d=>", nextnode->data);
        nextnode = nextnode->next;
    }
    printf("%d\n", nextnode->data);
}

int isprime(int num)
{
    if (num < 2) return 0;
    for (int i = 2; i < sqrt(num); i++) if (num % i == 0) return 0;
    return 1;
}


int main()
{
    Node *list = createNode(2);
    for (int i = 2; i < 100000; i++) if (isprime(i)) insertNode(i, list);
    printList(list);
}