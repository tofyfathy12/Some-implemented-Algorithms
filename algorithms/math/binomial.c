#include <stdio.h>
#include <string.h>

int org_n = 0, org_m = 0;

int binomial_helper(int n, int m, int *dp) {

    if (dp[n * (org_m + 1) + m] != -1) return dp[n * (org_m + 1) + m];

    if (n == 0 || m == 0) return dp[n * (org_m + 1) + m] = 1;
    if (n == 1) return dp[n * (org_m + 1) + m] = m + 1;
    if (m == 1) return dp[n * (org_m + 1) + m] = n + 1;

    return dp[n * (org_m + 1) + m] = binomial_helper(n - 1, m, dp) + binomial_helper(n, m - 1, dp);
}

int binomial(int n, int m) {
    org_n = n; org_m = m;
    int dp[(n + 1) * (m + 1)];
    memset(dp, -1, sizeof(dp));
    return binomial_helper(n, m, dp);
}

int main() {
    int n, m;

    printf("\n============== Binomial Calculator ==============");
    printf("\n=========== Choose(n, ) Calculator ! ===========");
    printf("\n=========== n C m Calculator ! ===========");
    printf("\nIt calculates (n)! / (n!.(n-m)!) :)\n\n");

    printf("Enter n: "); scanf("%d%*c", &n);
    printf("Enter m: "); scanf("%d%*c", &m);
    if (n < m) {
        printf("Error: n must be greater than or equal to m !!\n");
        return 1;
    }

    printf("\nBinomial(%d, %d) = Choose(%d, %d) = %d\n", n, m, n, m, binomial(m, n-m));

    printf("Goodbye !!\n");

    return 0;
}