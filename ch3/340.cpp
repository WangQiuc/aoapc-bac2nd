// UVa340 Master-Mind Hints
// wangqc

#include <stdio.h>
#include <string.h>
#define maxn 1010

int main()
{
    int n, a[maxn], b[maxn], ctra[9], ctrb[9];
    int kase = 0;
    while (scanf("%d", &n) == 1 && n)
    {
        printf("Game %d:\n", ++kase);
        memset(ctra, 0, sizeof(ctra));
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            ctra[a[i] - 1]++;
        }

        while (1)
        {
            int A = 0, B = 0;
            memset(ctrb, 0, sizeof(ctrb));
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &b[i]);
                if (b[i]) 
                    ctrb[b[i] - 1]++;
                if (a[i] == b[i]) 
                    A++;
            }
            if (b[0] == 0) break;
            for (int i = 0; i < 9; i++)
                B += ctra[i] < ctrb[i] ? ctra[i] : ctrb[i];
            printf("    (%d,%d)\n", A, B - A);
        }
    }
    return 0;
}