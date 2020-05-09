// UVa201 Squares
// wangqc

#include <stdio.h>
#include <string.h>
#define maxn 11

int H[maxn][maxn];
int V[maxn][maxn];

int main()
{
    int n, m, x, y, kase = 0;
    char s[2];
    while (scanf("%d%d", &n, &m) == 2)
    {
        if (kase++) printf("\n**********************************\n\n");
        printf("Problem #%d\n\n", kase);
        memset(H, 0, sizeof(H));
        memset(V, 0, sizeof(V));
        for (int i = 0; i < m; i++)
        {
            scanf("%s%d%d", s, &x, &y);
            if (s[0] == 'H') H[x][y] = 1;
            else V[y][x] = 1;   // as instruction, x is col, y is row for V
        }
        int no = 1;
        for (int len = 1; len < n; len++)
        {
            int cnt = 0;
            for (int i = 1; i + len <= n; i++)
                for (int j = 1; j + len <= n; j++)
                {
                    int ok = 1;
                    for (int k = 0; ok && k < len; k++)
                        ok = H[i][j+k] && H[i+len][j+k] && V[i+k][j] && V[i+k][j+len];                        
                    cnt += ok;
                }
            if (cnt) printf("%d square (s) of size %d\n", cnt, len);
            no &= !cnt;
        }
        if (no) printf("No completed squares can be found.\n");
    }
    return 0;
}
