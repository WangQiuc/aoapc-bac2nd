// UVa202 Repeating Decimals
// wangqc

#include <stdio.h>
#include <string.h>

#define maxn 3010

int main()
{
    int x, y, z, i, j, k, pos[maxn], hash[maxn];
    while ((scanf("%d %d", &x, &y)) == 2)
    {
        printf("%d/%d = ", x, y);
        memset(pos, 0, sizeof(pos));
        memset(hash, 0, sizeof(hash));
        for (j = 1; j < maxn; j++)
        {
            pos[j] = x / y, x %= y;
            if (i = hash[x])
                break;
            hash[x] = j;
            x *= 10;
        }
        printf("%d.", pos[1]);
        for (k = 2; k <= i; k++)
            printf("%d", pos[k]);
        printf("(");
        for (k = i + 1; k <= j && k <= 51; k++) 
            printf("%d", pos[k]);
        if (k == 52) printf("...");
        printf(")\n   %d = number of digits in repeating cycle\n\n", j - i);
    }
    return 0;
}