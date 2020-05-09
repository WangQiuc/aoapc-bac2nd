// UVa1599 Ideal Path
// wangqc

#include<iostream>
#include<cstring>
#include<queue>
#include<map>

using namespace std;

const int inf = 0x7fffffff;
const int maxn = 100005;
int n, m, d[maxn];
bool vis[maxn];

void rev_bfs(map<int, int> *graph)
{    
    memset(vis, 0, sizeof(vis));
    d[n-1] = 0, vis[n-1] = true;
    bool unfound = true;
    queue<int> q;
    q.push(n-1);
    while (unfound && !q.empty())
    {
        int u = q.front(); q.pop();
        for (auto pair : graph[u])
        {
            int v = pair.first;
            if (!vis[v])
            {
                d[v] = d[u] + 1;
                vis[v] = true;
                q.push(v);
            }
            if (!v) { unfound = false; break; }
        }
    }
}

void bfs(map<int, int> *graph)
{
    memset(vis, 0, sizeof(vis));
    vis[0] = true;
    vector<int> colors, q;
    q.push_back(0); 
    for (int i = d[0]; i > 0; i--)
    {
        int min_color = inf;
        for (int u : q)
            for (auto vw : graph[u])
                if (d[u] == d[vw.first] + 1 && min_color > vw.second)
                    min_color = vw.second;
        colors.push_back(min_color);
        vector<int> q2;
        for (int u : q)
            for (auto vw : graph[u])
            {
                int v = vw.first, w = vw.second;
                if (d[u] == d[v] + 1 && min_color == w)
                {
                    vis[v] = true;
                    q2.push_back(v);
                }
            }
        q = q2;
    }
    cout << d[0] << endl << colors[0];
    for (int i = 1; i < colors.size(); i++)
        cout << " " << colors[i];
    cout << endl; 
}

int main()
{
    while(cin >> n >> m)
    {
        map<int, int> graph[n];
        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            if (!graph[--u].count(--v) || w < graph[u][v])
                graph[u][v] = graph[v][u] = w;
        }
        rev_bfs(graph);
        bfs(graph);
    }
    return 0;
}
