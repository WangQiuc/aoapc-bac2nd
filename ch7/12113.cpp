// UVa 12113 Overlapping Squares
// wangqc
#include<cstdio>
#include<cstring>

char pic[5][15], p[5][9];
bool vis[9];

bool match()
{
    for (int i = 0; i < 5; i++)
        if (memcmp(pic[i], p[i], sizeof(p[i]))) return false;
    return true;
}

// exhausive enumerate 9C6 = 84 (select and place 6 squares in 9 places)
bool dfs(int d)
{
    if (match()) return true;
    if (d == 6) return false;               // less than 6 squares
    char p2[45];
    memcpy(p2, p, sizeof(p));
    for (int i = 0; i < 9; i++)
        if (!vis[i])
        {
            vis[i] = true;
            int r = i / 3, c = (i % 3) << 1;
            p[r][c+1] = p[r][c+3] = p[r+2][c+1] = p[r+2][c+3] = '_';
            p[r+1][c] = p[r+2][c] = p[r+1][c+4] = p[r+2][c+4] = '|';
            p[r+1][c+1] = p[r+1][c+2] = p[r+1][c+3] = p[r+2][c+2] = ' ';
            if (dfs(d+1)) return true;
            vis[i] = false;
            memcpy(p, p2, sizeof(p));       // set p back
        }
    return false;
}

int main()
{
    int kase = 0;
    while (fgets(pic[0], 15, stdin) && pic[0][0] != '0')
    {
        for (int i = 1; i < 5; i++)
            fgets(pic[i], 15, stdin);
        memset(p, ' ', sizeof(p));
        memset(vis, 0, sizeof(vis));
        printf("Case %d: %s\n", ++kase, (dfs(0) ? "Yes" : "No"));
    }
    return 0;
}

