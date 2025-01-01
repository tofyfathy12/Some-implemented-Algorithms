#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int char_to_digit(char digit);
char digit_to_char(double digit);
bool isprime(int n);
int gcd(int a, int b);
double *encrypt(char *message, double e, double n, long int *encrypted_length);
char *decrypt(double *encrypted_values, long int size, double d, double n);

int main()
{
    long int p, q;
    printf("Enter Upper Limit for P : ");
    scanf("%ld", &p);
    printf("Enter Upper Limit for Q : ");
    scanf("%ld", &q);

    for (int i = p; i >= 2; i--)
    {
        if (isprime(i))
        {
            p = i;
            break;
        }
    }

    for (int i = q; i >= 2; i--)
    {
        if (isprime(i))
        {
            q = i;
            break;
        }
    }

    long int n = p * q;
    long int m = (p - 1) * (q - 1);
    long int e = 2;
    while (gcd(m, e) != 1 && isprime(e) && e <= m) e++;
    long int k = 0;
    while ((k * m + 1) % e != 0) k++;
    long int d = (k * m + 1) / e;

    printf("n = %ld\n", n);
    printf("m = %ld\n", m);
    printf("e = %ld\n", e);
    printf("d = %ld\n", d);

    char *message = "Hello World!";
    long int length;
    double *encrypted_values = encrypt(message, e, n, &length);
    printf("Encrypted Message = ");
    for (long int i = 0; i < length; i++)
        printf("%c", (long int) encrypted_values[i] % 256);
    printf("\n");

    char *decrypted_message = decrypt(encrypted_values, length, d, n);
    printf("Decrypted Message = %s\n", decrypted_message);
    free(encrypted_values);
    free(decrypted_message);
}

double str_to_int(char *number)
{
    double result = 0;
    double ten = 1;
    for (int i = strlen(number) - 1; i >= 0; i--)
    {
        result += char_to_digit(number[i]) * ten;
        ten *= 10;
    }
    return result;
}

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

bool isprime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i < sqrt(n); i++) if (n % i == 0) return false;
    return true;
}

int char_to_digit(char digit)
{
    int num = digit;
    num -= 48;
    return num;
}

char digit_to_char(double digit)
{
    char result = digit;
    result += 48;
    return result;
}

double *encrypt(char *message, double e, double n, long int *encrypted_length)
{
    long int length = strlen(message);
    double *result = (double *)calloc(length, sizeof(double));
    for (long int i = 0; i < length; i++)
    {
        long int p = (long int) message[i];
        double c = 1;
        for (int j = 0; j < e; j++)
            c = fmod((c * p), n);
        result[i] = c;
    }

    *encrypted_length = length;
    return result;
}

char *decrypt(double *encrypted_values, long int size, double d, double n)
{
    char *result = (char *)calloc(size + 1, 1);
     for (long int i = 0; i < size; i++)
    {
        double c = encrypted_values[i];
        long int p = 1;
        for (int j = 0; j < d; j++)
            p = (long int) fmod((p * c),  n);
        result[i] = (char) p;
    }
    return result;
}

