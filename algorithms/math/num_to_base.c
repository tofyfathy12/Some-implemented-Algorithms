#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void get_integer(char *str, long int *n)
{
    bool valid = false;
    char input[1000];
    while (!valid)
    {
        printf("%s", str);
        fgets(input, 1000, stdin);
        input[strlen(input) - 1] = '\0';
        if (strlen(input) == 0)
        {
            printf("!!! Invalid Input !!!\n");
            printf("    Try Again\n");
            continue;
        }
        bool notint = false;
        int dots = 0;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!(isdigit(input[i]) || (input[i] == '-' && i == 0)))
            {
                notint = true;
                break;
            }
        }
        if (notint)
        {
            printf("!!! Invalid Input !!!\n");
            printf("    Try Again\n");
        }
        else
        {
            if (atof(input) > pow(2, 63) - 1)
            {
                printf("!!! OVERFLOW: NUMBER IS SO BIG !!!\n");
                printf("    Try Again\n");
                continue;
            }
            valid = true;
        }
    }
    *n = atol(input);
}

char digit_to_char(int digit)
{
    digit += 48;
    char result = (char) digit;
    return result;
}

char *convert_to_base(int num, int base)
{
    if (num == 0) return "0";
    int size = 0;
    while (pow(base, size) <= num) size ++;
    char *result = (char *)calloc(size + 1, sizeof(char));
    int temp = num;
    int i = size - 1;
    while (temp  > 0)
    {
        result[i] = digit_to_char(temp % base);
        temp /= base;
        i --;
    }
    return result;
}

int main()
{
    long int num, base;
    get_integer("Enter number : ", &num);
    do
    {
        get_integer("Enter base : ", &base);
        if (base <= 0) printf("Base can't be negative or zero\nTry Again\n");
    } while (base <= 0);
    printf("Number {%ld} in base 10 = {%s} in base %ld\n", num, convert_to_base(num, base), base);
    printf("PRESS ENTER TO EXIT...");
    char exit[2];
    fgets(exit, 2, stdin);
}