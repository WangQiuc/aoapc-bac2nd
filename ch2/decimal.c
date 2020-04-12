// wangqc

#include <stdio.h>

int main()
{
    int a, b, c, kase = 0;
    while (scanf("%d %d %d", &a, &b, &c) == 3 && a)
    {
        printf("Case %d: %.*f\n", ++kase, c, (double)a / b);
    }
    return 0;
}