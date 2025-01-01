#include <stdio.h>

int gcd(int num1, int num2)
{
    if (num1 == 1 || num2 == 1) return 1;
    int bigger_num = (num2 > num1) ? num2 : num1;
    int smaller_num = (num2 < num1) ? num2 : num1;
    int remainder = bigger_num % smaller_num;
    while (remainder > 0)
    {
        bigger_num = smaller_num;
        smaller_num = remainder;
        remainder = bigger_num % smaller_num;
    }
    return smaller_num;
}

int main()
{
    printf("The greatest common divisor of 200 and 120: %d", gcd(200, 120));
}