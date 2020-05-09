// UVa10305 Ordering Tasks
// wangqc

#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 105;
int n, m, id;
int graph[maxn][maxn];
int topo[maxn];
int v[maxn];

bool dfs(int x)
{
    v[x] = -1;
    for (int y = 1; y <= n; y++)
        if (graph[x][y])
            if (v[y] < 0 || (!v[y] && !dfs(y)))
                return false;
    v[x] = 1;
    topo[--id] = x;
    return true;
}

bool toposort()
{
    id = n;
    memset(v, 0, sizeof(v));
    for (int x = 1; x <= n; x++)
        if (!v[x] && !dfs(x)) 
            return false;
    return true;
}

int main()
{
    while(cin >> n >> m && n)
    {
        memset(graph, 0, sizeof(graph));
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            graph[x][y] = 1;
        }
        if (toposort())
            for (int i = 0; i < n-1; i++)
                cout << topo[i] << " ";
            cout << topo[n-1] << endl;
    }
    return 0;
}
