// UVa 1613 K-Graph Oddity
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 10000;
int degree, color[maxn];
vector<int> graph[maxn];

// should node x be colored with k ?
bool valid(int x, int k)
{
    for (int y : graph[x])
        if (color[y] == k) return false;
    return true;
}

void dfs(int x)
{
    for (int k = 1; k <= degree; k++) if (valid(x, k))
        {   color[x] = k; break; }
    for (int y : graph[x]) if (!color[y])
        dfs(y);
}

int main()
{
    int n, m, x, y, kase = 0;
    while (cin >> n >> m)
    {
        memset(color, 0, sizeof(color));
        for (x = 1; x <= n; x++) graph[x].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        degree = 0;
        for (x = 1; x <= n; x++)
            degree = max(degree, (int)graph[x].size());
        if (kase++) cout << endl;
        cout << (degree |= 1) << endl;
        dfs(1);
        for (x = 1; x <= n; x++)
            cout << color[x] << endl;
    }
    return 0;
}
