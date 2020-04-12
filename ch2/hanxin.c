// wangqc

#include <stdio.h>

int main()
{
    int a, b, c, s, kase = 0;
    while (scanf("%d %d %d", &a, &b, &c) == 3)
    {
        s = (a * 70 + b * 21 + c * 15) % 105;
        if (s >= 10 && s <= 100)
            printf("Case %d: %d\n", ++kase, s);
        else
            printf("Case %d: No answer\n", ++kase);
    }
    return 0;
}