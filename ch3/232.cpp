// UVa232 Crossword Answers
// wangqc

#include <stdio.h>
#include <string.h>

#define maxn 12

int main()
{
    int r, c, id, kase = 0;
    char s[maxn][maxn];
    int p[maxn*maxn];   // starting point id: p[id] = i*c + j
    while (scanf("%d %d", &r, &c) == 2)
    {
        id = 0;
        memset(s, 0, sizeof(s));
        memset(p, 0, sizeof(p));
        for (int i = 0; i < r; i++)
        {
            scanf("%s", s[i]);
            int first = 1;
            for (int j = 0; j < c; j++)
            {
                if (first && s[i][j] != '*') p[i*c+j] = ++id;
                first = (i && s[i][j] != '*' && s[i-1][j+1] != '*') ? 0 : 1;
            }
        }
        if (kase) printf("\n");
        printf("puzzle #%d:\nAcross\n", ++kase);
        for (int x = 0; x < r * c; x++)
        {
            if (!p[x]) continue;
            int i = x / c, j = x % c;
            if (!j || s[i][j-1] == '*')
            {
                printf(" %2d.", p[x]);
                while (j < c && s[i][j] != '*')
                    printf("%c", s[i][j++]);
                printf("\n");
            }
        }
        printf("Down\n");
        for (int x = 0; x < r * c; x++)
        {
            if (!p[x]) continue;
            int i = x / c, j = x % c;
            if (!i || s[i-1][j] == '*')
            {
                printf(" %2d.", p[x]);
                while (i < r && s[i][j] != '*')
                    printf("%c", s[i++][j]);
                printf("\n");
            }
        }        
    }
    return 0;
}