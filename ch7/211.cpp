// UVa 211 The Domino Effect
// wangqc
#include<cstdio>
#include<cstring>

const int maxn = 10;
int id[maxn][maxn], pips[maxn][maxn], bones[maxn][maxn];
bool used[maxn*3];
int cnt;

void init()
{
    int k = 0;
    for (int i = 0; i < 7; i++)
        for (int j = i; j < 7; j++)
            id[i][j] = id[j][i] = ++k;
}

bool valid(int x, int y) { return 0 <= x && x < 7 && 0 <= y && y < 8 && !bones[x][y]; }

void print(int board[][maxn])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%4d", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

void dfs(int x0, int y0)
{   // reach the end and all 56 slots must be filled
    if (x0 == 7) 
    {   cnt++; print(bones); }
    else if (y0 == 8) 
        dfs(x0+1, 0);                  // go to next line   
    else if (bones[x0][y0]) 
        dfs(x0, y0+1);                 // go to next slot 
    else for (int i = 0; i < 2; i++)   // fill this slot with a bid
    {   // horizontal (x0, y0+1), or vertical (x0+1, y0)
        int x = x0 + i, y = y0 + (i ^ 1), bid; 
        if (valid(x, y) && !used[bid = id[pips[x0][y0]][pips[x][y]]])
        {
            bones[x0][y0] = bid, bones[x][y] = bid, used[bid] = true;
            dfs(x0, y0+1);
            bones[x0][y0] = bones[x][y] = used[bid] = 0;
        }
    }
}

int main()
{
    init();
    int x, kase = 0;
    while (scanf("%d", &x) == 1)
    {
        if (kase++) printf("\n\n\n");
        memset(used, 0, sizeof(used));
        memset(pips, 0, sizeof(pips));
        memset(bones, 0, sizeof(bones));
        cnt = 0, pips[0][0] = x;
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 8; j++)
                if (i || j) { scanf("%d", &x); pips[i][j] = x; }
        printf("Layout #%d:\n\n", kase);
        print(pips);
        printf("Maps resulting from layout #%d are:\n\n", kase);
        dfs(0, 0);
        printf("There are %d solution(s) for layout #%d.\n", cnt, kase);
    } 
    return 0;
}
