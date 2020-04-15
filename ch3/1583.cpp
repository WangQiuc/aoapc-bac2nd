// UVa1583 Digital Generator
// wangqc

#include <stdio.h>
#include <string.h>
#define maxn 100001

int gen[maxn];

int main()
{
    int n, x;
    memset(gen, 0, sizeof(gen));
    for (int i = 1; i < maxn; i++)
    {
        int x = i, y = i;
        while (x)
        {
            y += x % 10;
            x /= 10;
        }
        if(!gen[y] && y < maxn) gen[y] = i;
    }
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &x);
        printf("%d\n", gen[x]);
    }
    return 0;
}