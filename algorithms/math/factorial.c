#include <stdio.h>

double memo[1];
double factorial(double n)
{
    memo[0] = 2;
    double result;
    for (int i = 1; i < n+1; i++)
    {
        if (i == 1 || i == 2) result = i;
        else result = i*memo[0];
        memo[0] = result;
    }
    return result;
}

int main()
{
    double n;
    printf("Enter the value of n: ");
    scanf("%lf\0", &n);
    for (double i = 1; i< n+1; i++) printf("factorial(%.0lf) = %.0lf\n", i, factorial(i));
}