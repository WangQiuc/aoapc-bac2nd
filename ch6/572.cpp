// UVa572 Oil Deposits
// wangqc

#include <cstdio>
#include <cstring>

const int maxn = 105;
char graph[maxn][maxn];
int m, n;

void dfs(int x, int y)
{
    if (x < 0 || x >= m || y < 0 || y >= n || graph[x][y] != '@') return;
    graph[x][y] = '*';
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (dx || dy) dfs(x + dx, y + dy);
}

int main()
{
    while (scanf("%d%d", &m, &n) == 2 && m && n)
    {
        for (int i = 0; i < m; i++) scanf("%s", graph[i]);
        int cnt = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (graph[i][j] == '@') 
                    dfs(i, j), cnt++;
        printf("%d\n", cnt);
    }
    return 0;
}
