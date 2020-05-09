// UVa512 Spreadsheet Tracking
// wangqc

#include <stdio.h>
#include <string.h>
#define maxd 10000

struct Command
{
    char c[5];
    int r1, r2, c1, c2;
    int cnt, x[20];
} cmd[maxd];

int R, C, n;

int simulate(int *r, int *c)
{
    for (int i = 0; i < n; i++)
    {
        if (cmd[i].c[0] == 'E')
        {
            if (cmd[i].r1 == *r && cmd[i].c1 == *c)
                *r = cmd[i].r2, *c = cmd[i].c2;
            else if (cmd[i].r2 == *r && cmd[i].c2 == *c)
                *r = cmd[i].r1, *c = cmd[i].c1;
        }
        else
        {
            int dr = 0, dc = 0;
            for (int j = 0; j < cmd[i].cnt; j++)
            {
                int x = cmd[i].x[j];
                if (cmd[i].c[0] == 'I')
                {
                    if (cmd[i].c[1] == 'R' && x <= *r) dr++;
                    if (cmd[i].c[1] == 'C' && x <= *c) dc++;
                }
                else
                {
                    if (cmd[i].c[1] == 'R' && x == *r) return 0;
                    if (cmd[i].c[1] == 'C' && x == *c) return 0;
                    if (cmd[i].c[1] == 'R' && x < *r) dr--;
                    if (cmd[i].c[1] == 'C' && x < *c) dc--;
                }
            }
            *r += dr, *c += dc;
        }
    }
    return 1;
}

int main()
{
    int r, c, q, kase = 0;
    while (scanf("%d%d%d", &R, &C, &n) == 3 && R)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%s", cmd[i].c);
            if (cmd[i].c[0] == 'E')
                scanf("%d%d%d%d", &cmd[i].r1, &cmd[i].c1, &cmd[i].r2, &cmd[i].c2);
            else
            {
                scanf("%d", &cmd[i].cnt);
                for (int j = 0; j < cmd[i].cnt; j++)
                    scanf("%d", &cmd[i].x[j]);
            }
        }
        if(kase) printf("\n");
        printf("Spreadsheet #%d\n", ++kase);

        scanf("%d", &q);
        while (q--)
        {
            scanf("%d%d", &r, &c);
            printf("Cell data in (%d,%d) ", r, c);
            simulate(&r, &c) ? printf("moved to (%d,%d)\n", r, c) : printf("GONE\n");
        }
    }
    return 0;
}
