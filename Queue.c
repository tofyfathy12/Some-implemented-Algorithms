#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAME 5

int frames[MAX_FRAME] = {0};

void insert(int n)
{
    for (int i = 0; i < MAX_FRAME; i++)
    {
        if (frames[i] == n)
        {
            printf("The Element %d already exists in the frame at page %d\n", n, i);
            return;
        }
    }
    for (int i = 0; i < MAX_FRAME - 1; i++)
    {
        frames[i] = frames[i + 1];
    }
    frames[MAX_FRAME - 1] = n;
}

void print_frame()
{
    for (int i = 0; i < MAX_FRAME; i++) printf("%d ", frames[i]);
    printf("\n");
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 6, 3, -1, 2, 10};
    int length = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < length; i++)
    {
        insert(arr[i]);
        print_frame();
    }
}