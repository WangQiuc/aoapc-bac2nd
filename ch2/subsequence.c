// wangqc

#include <stdio.h>

int main()
{
    int n, m, kase = 0;
    while (scanf("%d %d", &n, &m) == 2 && n && n < m)
    {
        double s = 0;
        for (double i = n; i <= m; i++)
            s += 1.0 / (i * i);
        printf("Case %d: %.5f\n", ++kase, s);
    }
    return 0;
}