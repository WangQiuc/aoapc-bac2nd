// UVa 208 Firetruck
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 22;
bool edge[maxn][maxn], vis[maxn], reach[maxn];   // connected to dst node;
int n, cnt, path[maxn];

void dfs_rev(int x)
{
    reach[x] = true;
    for (int y = 1; y < maxn; y++)
        if (edge[x][y] && !reach[y]) dfs_rev(y);
}

void dfs(int x, int i)
{
    if (x == n)
    {
        for (int j = 0; j < i; j++) cout << path[j] << " ";
        cout << n << endl;
        cnt++;
    }
    if (reach[x])
    {
        vis[x] = true, path[i] = x;
        for (int y = 1; y < maxn; y++)
            if (edge[x][y] && !vis[y]) dfs(y, i+1);
        vis[x] = false;
    }
}

int main()
{
    int u, v, kase = 0;
    while (cin  >> n && n)
    {
        memset(edge, 0, sizeof(edge));
        memset(vis, 0, sizeof(vis));
        memset(reach, 0, sizeof(reach));
        memset(path, 0, sizeof(path));
        cnt = 0;
        while (cin >> u >> v && u)
            edge[u][v] = edge[v][u] = true;
        cout << "CASE " << ++kase << ":\n";
        dfs_rev(n);
        dfs(1, 0);
        cout << "There are " << cnt << " routes from the firestation to streetcorner " << n << ".\n";
    }
    return 0;
}
