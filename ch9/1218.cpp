// UVa 1218 Perfect Service
// wangqc
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 10005;
const int INF = 0x3ffffff;

vector<int> graph[maxn], nodes;
// d[x][0] x is server, child y can be server or not
// d[x][1] x is not server and i's parent is server, child y cannot be server
// d[x][2] x and parent are not server, one and only one child y is server
int parent[maxn], d[maxn][3];

void dfs(int x, int p)
{
    nodes.push_back(x);
    parent[x] = p;
    for (int y : graph[x]) if (y != p) 
        dfs(y, x);
}

int main()
{
    int x, y, n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) 
            graph[i].clear();
        for (int i = 0; i < n-1; i++)
        {
            cin >> x >> y;
            graph[--x].push_back(--y);
            graph[y].push_back(x);
        }
        nodes.clear();
        dfs(0, -1);
        for (int i = nodes.size()-1; i >= 0; i--)   // start dp from leaf node
        {
            x = nodes[i], d[x][0] = 1, d[x][1] = 0;
            for (int y : graph[x]) if (y != parent[x])
            {
                d[x][0] = min(d[x][0] + min(d[y][0], d[y][1]), INF);
                d[x][1] = min(d[x][1] + d[y][2], INF);
            }
            d[x][2] = INF;
            for (int y : graph[x]) if (y != parent[x])
                // d[x][1] = sum(d[y][2] for y in G[x]), then select one y to be server
                d[x][2] = min(d[x][2], d[x][1] - d[y][2] + d[y][0]);
        }
        cout << min(d[0][0], d[0][2]) << endl;
        cin >> n;
    }
    return 0;
}
