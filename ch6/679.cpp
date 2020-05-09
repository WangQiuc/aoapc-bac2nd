// UVa679 Dropping Balls
// wangqc

#include <cstdio>
#include <cstring>

int main()
{
    int d, n, kase;
    scanf("%d", &kase);
    while (kase--)
    {
        scanf("%d%d", &d, &n);
        int k = 1;
        for (int i = 1; i < d; i++)
        {
            if (n & 1) k <<= 1, n = (n+1)>>1;
            else k = (k<<1)+1, n >>= 1;
        }
        printf("%d\n", k);
    }
    return 0;
}
