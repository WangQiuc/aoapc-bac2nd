// UVa1368 DNA Consensus String
// wangqc

#include <stdio.h>
#include <string.h>

#define maxn 1010

int c2i(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return 4;
}

int main()
{
    int m, n, T, ctr[maxn][5];
    const char *DNA = "ACGT";
    char s[maxn];
    
    scanf("%d", &T);
    while (T--)
    {
        memset(ctr, 0, sizeof(ctr));
        scanf("%d %d", &m, &n);
        for (int i = 0; i < m; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < n; j++)
                ctr[j][c2i(s[j])]++;
        }
        int x, k, d = 0;
        for (int i = 0; i < n; i++)
        {
            x = k = 0;
            for (int j = 0; j < 4; j++)
            {
                if (x < ctr[i][j]) { x = ctr[i][j]; k = j; }
                d += ctr[i][j];
            }
            d -= x;
            printf("%c", DNA[k]);
        }
        printf("\n%d\n", d);
    }
    return 0;
}