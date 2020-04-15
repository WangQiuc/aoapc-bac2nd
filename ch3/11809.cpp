// UVa1588 Kickdown
// wangqc

#include <stdio.h>
#include <string.h>
#include <math.h> 

#define eps 1e-4

double M[11][33];
int E[11][33];

int main()
{
    int i, j;
    char s[25];
    for (i = 0; i <= 9; i++)
        for (j = 1; j <= 30; j++)
        {
            long long e = pow(2, j) - 1;
            double m = 1 - pow(2, -i-1);
            double t = log10(m) + e * log10(2);
            E[i][j] = t;
            M[i][j] = pow(10, t - E[i][j]);
        }
    while (scanf("%s", s) && (strcmp(s, "0e0")))
    {
        s[17] = ' ';
        double a;
        int b;
        sscanf(s, "%lf %d", &a, &b);
        int i, j, f = 1;
        for (i = 0; i <= 9 && f; i++)
            for (j = 1; j <= 30 && f; j++)
                f = b != E[i][j] || fabs(a - M[i][j]) > eps;
        printf("%d %d\n", i-1, j-1);
            
    }
    return 0;
}