#include <stdio.h>

double memo[2];
double fib(double n)
{
    double result;
    for (int i = 1; i < n+1; i++)
    {
        if (i == 1 || i == 2) result = 1;
        else result = memo[0] + memo[1];
        memo[0] = memo[1];
        memo[1] = result;
    }
    return result;
}

int main()
{
    memo[0] = 1;
    memo[1] = 1;
    double n;
    printf("Enter the value of n: ");
    scanf("%lf\0", &n);
    for (double i = 1; i < n+1; i++) printf("fib of %.0lf: %.0lf\n", i, fib(i));
}