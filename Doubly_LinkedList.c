#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nd
{
    int data;
    struct nd *next;
    struct nd *prev;
} Node;

typedef struct LL
{
    Node *head;
    Node *tail;
    int length;
} LinkedList;

Node *create_node(int data);
void set_data(Node *node, int new_data);
void set_next(Node *node, Node *next);
void set_prev(Node *node, Node *prev);
int get_data(Node *node);
Node *get_next(Node *node);
Node *get_prev(Node *node);
LinkedList *create_list(Node *head);
bool is_empty(LinkedList *list);
void insert_last(LinkedList *list, int data);
void insert_first(LinkedList *list, int data);
void print_list(LinkedList *list);
void print_list_reversed(LinkedList *list);
void free_list(LinkedList *list);
LinkedList *reversed(LinkedList *list);
LinkedList *copy(LinkedList *org);
LinkedList *concat(LinkedList *list1, LinkedList *list2);
int delete(LinkedList *list, int index);
int insert_at(LinkedList *list, int index, int data);
LinkedList *sub_list(LinkedList *list, int start_index, int end_index);

int main(void)
{
    LinkedList *mylist = create_list(NULL);
    printf("Printing mylist: length = %d\n", mylist->length);
    print_list(mylist);
    print_list_reversed(mylist);
    for (int i = 1; i <= 10; i++)
    {
        insert_last(mylist, i);
    }
    printf("Printing mylist: length = %d\n", mylist->length);
    print_list(mylist);
    print_list_reversed(mylist);

    LinkedList *listmy = reversed(mylist);
    printf("Printing listmy: length = %d\n", listmy->length);
    print_list(listmy);
    print_list_reversed(listmy);

    LinkedList *mylist1 = copy(mylist);
    LinkedList *listmy1 = copy(listmy);
    free_list(mylist);
    free_list(listmy);

    printf("Printing mylist1: length = %d\n", mylist1->length);
    print_list(mylist1);
    print_list_reversed(mylist1);
    printf("Printing listmy1: length = %d\n", listmy1->length);
    print_list(listmy1);
    print_list_reversed(listmy1);

    LinkedList *mylistmy1 = concat(mylist1, listmy1);
    printf("Printing mylistmy1: length = %d\n", mylistmy1->length);
    print_list(mylistmy1);
    print_list_reversed(mylistmy1);
    int length = mylistmy1->length;
    int index = length / 2;
    for (int i = index; i < length; i++)
    {
        delete (mylistmy1, index);
        printf("%s mylistmy1: length = %d\n", (i == length - 1) ? "Final" : "Current", mylistmy1->length);
        print_list(mylistmy1);
        print_list_reversed(mylistmy1);
    }
    insert_at(mylistmy1, 0, 17);
    printf("Printing mylistmy1: length = %d\n", mylistmy1->length);
    print_list(mylistmy1);
    print_list_reversed(mylistmy1);
    insert_at(mylistmy1, mylistmy1->length, 19);
    printf("Printing mylistmy1: length = %d\n", mylistmy1->length);
    print_list(mylistmy1);
    print_list_reversed(mylistmy1);
    insert_at(mylistmy1, 1, 21);
    printf("Printing mylistmy1: length = %d\n", mylistmy1->length);
    print_list(mylistmy1);
    print_list_reversed(mylistmy1);

    free_list(mylist1);
    free_list(listmy1);
    free_list(mylistmy1);

    LinkedList *mylist2 = create_list(NULL);
    printf("Printing mylist2: length = %d\n", mylist2->length);
    print_list(mylist2);
    print_list_reversed(mylist2);
    for (int i = 1; i <= 15; i += 2)
    {
        insert_at(mylist2, mylist2->length, i);
        printf("%s mylist2: length = %d\n", (i == 15) ? "Final" : "Current", mylist2->length);
        print_list(mylist2);
        print_list_reversed(mylist2);
    }

    LinkedList *sub = sub_list(mylist2, 2, 6);
    printf("Printing sublist: length = %d\n", sub->length);
    print_list(sub);
    print_list_reversed(sub);
    int sublen = sub->length;
    for (int i = 0; i < sublen; i++)
    {
        delete (sub, sublen - i - 1);
        printf("%s sublist: length = %d\n", (i == sublen - 1) ? "Final" : "Current", sub->length);
        print_list(sub);
        print_list_reversed(sub);
    }
    printf("Printing mylist2: length = %d\n", mylist2->length);
    print_list(mylist2);
    print_list_reversed(mylist2);

    free_list(mylist2);
    free_list(sub);
}

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Error: Can't allocate memory for a new node !!\n");
        return NULL;
    }
    else
    {
        set_data(new_node, data);
        set_next(new_node, NULL);
        set_prev(new_node, NULL);
        return new_node;
    }
}

void set_data(Node *node, int new_data)
{
    if (node != NULL)
        node->data = new_data;
    else
        printf("Error %d: given node is NULL !!\n", __LINE__);
}

void set_next(Node *node, Node *next)
{
    if (node != NULL)
        node->next = next;
    else
        printf("Error %d: given node is NULL !!\n", __LINE__);
}

void set_prev(Node *node, Node *prev)
{
    if (node != NULL)
        node->prev = prev;
    else
        printf("Error %d: given node is NULL !!\n", __LINE__);
}

int get_data(Node *node)
{
    if (node != NULL)
        return node->data;
    else
    {
        printf("Error %d: given node is NULL !!\n", __LINE__);
        exit(EXIT_FAILURE);
    }
}

Node *get_next(Node *node)
{
    if (node != NULL)
        return node->next;
    else
    {
        printf("Error %d: given node is NULL !!\n", __LINE__);
        return NULL;
    }
}

Node *get_prev(Node *node)
{
    if (node != NULL)
        return node->prev;
    else
    {
        printf("Error %d: given node is NULL !!\n", __LINE__);
        return NULL;
    }
}

LinkedList *create_list(Node *head)
{
    LinkedList *new_list = (LinkedList *)malloc(sizeof(LinkedList));
    if (new_list != NULL)
    {
        new_list->length = 0;
        if (head == NULL)
        {
            new_list->head = NULL;
            new_list->tail = NULL;
        }
        else
        {
            Node *cur_node = head;
            new_list->head = head;
            while (get_next(cur_node) != NULL)
            {
                new_list->length++;
                cur_node = get_next(cur_node);
            }
            new_list->length++;
            new_list->tail = cur_node;
        }
    }
    return new_list;
}

bool is_empty(LinkedList *list)
{
    return (list->head == NULL);
}

void insert_last(LinkedList *list, int data)
{
    if (is_empty(list))
    {
        list->length = 1;
        list->head = create_node(data);
        list->tail = list->head;
    }
    else
    {
        list->length++;
        Node *new_node = create_node(data);
        set_next(list->tail, new_node);
        set_prev(new_node, list->tail);
        list->tail = new_node;
    }
}

void insert_first(LinkedList *list, int data)
{
    if (is_empty(list))
    {
        list->length = 1;
        list->tail = create_node(data);
        list->head = list->tail;
    }
    else
    {
        list->length++;
        Node *new_node = create_node(data);
        set_next(new_node, list->head);
        set_prev(list->head, new_node);
        list->head = new_node;
    }
}

void print_list(LinkedList *list)
{
    printf("{");
    Node *iter;
    if (!is_empty(list))
    {
        for (iter = list->head; get_next(iter) != NULL; iter = get_next(iter))
        {
            printf("%d, ", get_data(iter));
        }
        printf("%d}\n", get_data(iter));
    }
    else
    {
        printf("}\n");
    }
}

void print_list_reversed(LinkedList *list)
{
    printf("{");
    Node *iter;
    if (!is_empty(list))
    {
        for (iter = list->tail; get_prev(iter) != NULL; iter = get_prev(iter))
        {
            printf("%d, ", get_data(iter));
        }
        printf("%d}\n", get_data(iter));
    }
    else
    {
        printf("}\n");
    }
}

void free_list(LinkedList *list)
{
    if (!is_empty(list))
    {
        Node *cur_node = list->head;
        while (cur_node != NULL)
        {
            Node *next_node = get_next(cur_node);
            free(cur_node);
            cur_node = next_node;
        }
    }
    free(list);
    list = NULL;
}

LinkedList *reversed(LinkedList *list)
{
    LinkedList *new_list = create_list(NULL);
    if (new_list != NULL)
    {
        if (!is_empty(list))
        {
            Node *cur = list->tail;
            Node *cur_new = create_node(get_data(cur));
            new_list->head = cur_new;
            Node *prev_new = cur_new;
            cur = get_prev(cur);
            while (cur != NULL)
            {
                cur_new = create_node(get_data(cur));
                set_next(prev_new, cur_new);
                set_prev(cur_new, prev_new);
                prev_new = cur_new;
                cur = get_prev(cur);
            }
            new_list->tail = cur_new;
            new_list->length = list->length;
        }
    }
    return new_list;
}

LinkedList *copy(LinkedList *org)
{
    LinkedList *new_list = create_list(NULL);
    if (new_list != NULL)
    {
        if (!is_empty(org))
        {
            new_list->length = org->length;
            new_list->head = create_node(get_data(org->head));
            if (new_list->head == NULL)
            {
                printf("Error: Couldn't allocate memory while copying list !!\n");
                exit(EXIT_FAILURE);
            }
            new_list->tail = new_list->head;
            for (Node *iter = get_next(org->head); iter != NULL; iter = get_next(iter))
            {
                Node *new_node = create_node(get_data(iter));
                if (new_node == NULL)
                {
                    printf("Error: Couldn't allocate memory while copying list !!\n");
                    free_list(new_list);
                    exit(EXIT_FAILURE);
                }
                set_next(new_list->tail, new_node);
                set_prev(new_node, new_list->tail);
                new_list->tail = new_node;
            }
        }
    }
    return new_list;
}

LinkedList *concat(LinkedList *list1, LinkedList *list2)
{
    LinkedList *new_list = copy(list1);
    new_list->length = list1->length + list2->length;
    for (Node *iter = list2->head; iter != NULL; iter = get_next(iter))
    {
        Node *new_node = create_node(get_data(iter));
        if (new_node == NULL)
        {
            printf("Error: Couldn't allocate memory while concatinating lists !!\n");
            free_list(new_list);
            exit(EXIT_FAILURE);
        }
        set_next(new_list->tail, new_node);
        set_prev(new_node, new_list->tail);
        new_list->tail = new_node;
    }
    return new_list;
}

int delete(LinkedList *list, int index)
{
    if (is_empty(list))
    {
        printf("Error: Deleting from empty list !!\n");
        return -1;
    }
    else if (index >= list->length || index < 0)
    {
        printf("Error: Index out of range !!\n");
        return -1;
    }
    else
    {
        int i = 0;
        Node *cur_node = list->head, *prev_node = NULL;
        while (i < index)
        {
            prev_node = cur_node;
            cur_node = get_next(cur_node);
            i++;
        }
        Node *next_node = get_next(cur_node);
        if (index > 0 && index < (list->length - 1))
        {
            set_next(prev_node, next_node);
            set_prev(next_node, prev_node);
        }
        else if (index == 0)
            list->head = get_next(cur_node);
        else if (index == (list->length - 1))
        {
            set_next(prev_node, next_node);
            list->tail = prev_node;
        }
        set_next(cur_node, NULL);
        set_prev(cur_node, NULL);
        free(cur_node);
        cur_node = NULL;
        list->length--;
        if (list->length == 0)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        return 0;
    }
}

int insert_at(LinkedList *list, int index, int data)
{
    if (index > list->length)
    {
        printf("Error: Insertion Index out of range !!\n");
        return -1;
    }
    else
    {
        int i = 0;
        Node *cur_node = list->head, *prev_node = NULL;
        while (i < index)
        {
            i++;
            prev_node = cur_node;
            cur_node = get_next(cur_node);
        }
        Node *new_node = create_node(data);
        set_prev(new_node, prev_node);
        set_next(new_node, cur_node);
        if (i > 0)
            set_next(prev_node, new_node);
        if (i < list->length)
            set_prev(cur_node, new_node);
        if (i == 0)
        {
            list->head = new_node;
            if (list->length == 0)
            {
                list->tail = new_node;
            }
        }
        else if (i == list->length)
        {
            list->tail = new_node;
        }
        list->length++;
    }
    return 0;
}

LinkedList *sub_list(LinkedList *list, int start_index, int end_index)
{
    if (is_empty(list))
    {
        printf("Error: Sublisting from empty list !!\n");
        return NULL;
    }
    else if (!(start_index >= 0 && start_index <= end_index && end_index >= start_index && end_index <= list->length))
    {
        printf("Error: Incorrect sublisting boundries !!\n");
        return NULL;
    }
    else
    {
        int i = 0;
        Node *cur_node = list->head;
        Node *head_node, *tail_node;
        while (i < start_index)
        {
            i++;
            cur_node = get_next(cur_node);
        }
        head_node = create_node(get_data(cur_node));
        if (head_node == NULL)
        {
            printf("Error: Couldn't allocate memory while making sublist !!\n");
            exit(EXIT_FAILURE);
        }
        Node *cur_new = head_node;
        cur_node = get_next(cur_node);
        i++;
        while (i < end_index)
        {
            Node *new_node = create_node(get_data(cur_node));
            if (new_node == NULL)
            {
                printf("Error: Couldn't allocate memory while making sublist !!\n");
                Node *cur_node = head_node;
                while (cur_node != NULL)
                {
                    Node *next_node = get_next(cur_node);
                    free(cur_node);
                    cur_node = next_node;
                }
                exit(EXIT_FAILURE);
            }
            set_next(cur_new, new_node);
            set_prev(new_node, cur_new);
            cur_new = new_node;
            cur_node = get_next(cur_node);
            i++;
        }
        tail_node = cur_new;
        LinkedList *sub_list = (LinkedList *)malloc(sizeof(LinkedList));
        if (sub_list != NULL)
        {
            sub_list->head = head_node;
            sub_list->tail = tail_node;
            sub_list->length = end_index - start_index;
        }
        else
        {
            Node *cur_node = head_node;
            while (cur_node != NULL)
            {
                Node *next_node = get_next(cur_node);
                free(cur_node);
                cur_node = next_node;
            }
        }
        return sub_list;
    }
}
