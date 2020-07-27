// UVa 12661 Funny Car Racing
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 305, inf = 0x7f7f7f7f;
int d[maxn], vis[maxn];

struct Edge
{
    int src, dst, a, b, t;
    Edge(int s, int d, int a, int b, int t): src(src), dst(d), a(a), b(b), t(t) {}
};

struct Node
{
    int i, d;
    Node(int i=0, int d=0): i(i), d(d) {}
    bool operator < (const Node &rhs) const { return d > rhs.d; }
};

vector<Edge> edges;
vector<int> G[maxn];

void add_edge(int src, int dst, int a, int b, int t)
{
    G[src].push_back(edges.size());
    edges.push_back(Edge(src, dst, a, b, t));
}

int dijkstra(int s, int t)
{
    memset(vis, 0, sizeof(vis));
    memset(d, inf, sizeof(d));
    priority_queue<Node> pq;
    pq.push(Node(s, 0));
    d[s] = 0;
    while(!pq.empty())
    {
        int src = pq.top().i; pq.pop();
        if(src == t) break;
        if(vis[src]) continue;
        vis[src] = true;
        for(int i : G[src])
        {
            Edge &e = edges[i];
            int wt = d[src]%(e.a+e.b)+e.t > e.a ? e.a+e.b-d[src]%(e.a+e.b) : 0;
            if(d[e.dst] > d[src] + e.t + wt)
            {
                d[e.dst] = d[src] + e.t + wt;
                pq.push(Node(e.dst, d[e.dst]));
            }
        }
    }
    return d[t];
}

int main()
{
    int n, m, s, t, kase = 0;
    while(cin >> n >> m >> s >> t)
    {
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
        int u, v, a, b, tt;
        for(int i = 0; i < m; i++)
        {
            cin >> u >> v >> a >> b >> tt;
            if (a >= tt) add_edge(u, v, a, b, tt);
        }
        cout << "Case " << ++kase << ": " << dijkstra(s, t) << endl;
    }
    return 0;
}
