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

long int get_ascii_number(char letter)
{
    long int result = (long int) letter;
    return result;
}


double BigNumber_mod(double number, long int power, long int n) // calculated (number ^ power) mod n
{
    double result = 1;
    for (long int i = 0; i < power; i++)
    {
        result = fmod((result * number), n);
    }
    return result;
}

double *get_encrypted_msg(long int e, long int n, char *msg)
{
    long int length = strlen(msg);
    double *encrypted = (double *)malloc(length * sizeof(double));
    for (long int i = 0; i < length; i++)
    {
        encrypted[i] = BigNumber_mod(get_ascii_number(msg[i]), e, n);
    }
    return encrypted;
}

char *get_original_msg(long int d, long int m, double *encryped_msg, long int size)
{
    char *msg = (char *)calloc((size + 1), sizeof(char));
    for (long int i = 0; i < size; i++)
    {
        msg[i] = (char) ((long int)BigNumber_mod(encryped_msg[i], d, m));
    }
    return msg;
}

void print_array(double *array, long int size)
{
    for (long int i = 0; i < size; i++)
        printf("%.0lf ", array[i]);
    printf("\n");
}

long int gcd(long int a, long int b)
{
    long int bigger = (a > b) ? a : b;
    long int smaller = a + b - bigger;
    if (smaller == 0)
        return bigger;
    return gcd(smaller, bigger % smaller);
}

long int isprime(long int num)
{
    if (num < 2) return 0;
    for (long int i = 2; i < sqrt(num); i++)
    {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main()
{
    long int p_upper_bound;
    long int q_upper_bound;
    long int p;
    long int q;
    get_integer("Enter Upper bound for p : ", &p_upper_bound);
    get_integer("Enter Upper bound for q : ", &q_upper_bound);
    while (!isprime(p_upper_bound)) p_upper_bound--;
    while (!isprime(q_upper_bound)) q_upper_bound--;
    p = p_upper_bound;
    q = q_upper_bound;
    long int n = p * q;
    long int m = (p - 1) * (q - 1);
    long int e = 1;
    while (gcd(m, e) != 1 || !isprime(e)) e ++;
    long int k = 1;
    while ((k * m + 1) % e != 0) k ++;
    long int d = (k * m + 1) / e;

    printf("n = %ld\n", n);
    printf("m = %ld\n", m);
    printf("e = %ld\n", e);
    printf("d = %ld\n", d);

    char msg[1000];
    printf("Enter message : ");
    fgets(msg, 1000, stdin);
    msg[strlen(msg) - 1] = 0;

    long int length = strlen(msg);
    double *encrypted_msg = get_encrypted_msg(e, n, msg);
    print_array(encrypted_msg, length);
    char *encrypted_msg_letters = (char *)calloc(length + 1, sizeof(char));
    for (long int i = 0; i < length; i++)
    {
        encrypted_msg_letters[i] = (char) ((long int) BigNumber_mod(encrypted_msg[i], 1, 256));
    }
    printf("Encryped Message = %s\n", encrypted_msg_letters);
    char *original_msg = get_original_msg(d, n, encrypted_msg, length);
    printf("Original Message = %s\n", original_msg);
}