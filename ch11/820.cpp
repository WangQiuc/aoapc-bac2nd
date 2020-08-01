// UVa 820 Internet Bandwidth
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 105, inf = 1e9;

struct Edge
{
    int src, dst, cap, flow;
    Edge(int s, int d, int k, int f): src(s), dst(d), cap(k), flow(f) {}
};

struct EdmondsKarp
{
    int d[maxn], path[maxn];
    vector<Edge> edges;
    vector<int> G[maxn];

    void init(int n)
    {
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void add_edge(int src, int dst, int cap)
    {
        int m = edges.size();
        G[src].push_back(m);
        G[dst].push_back(m^1);
        edges.push_back(Edge(src, dst, cap, 0));
        edges.push_back(Edge(dst, src, cap, 0));    // undirected edge
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        for(;;)
        {
            memset(d, 0, sizeof(d));
            d[s] = inf;
            queue<int> q;
            q.push(s);
            while(!q.empty())
            {
                int src = q.front(); q.pop();
                for(int i : G[src])
                {
                    Edge &e = edges[i];
                    if(!d[e.dst] && e.cap > e.flow)
                    {
                        d[e.dst] = min(d[src], e.cap-e.flow);
                        path[e.dst] = i;
                        q.push(e.dst);
                    }
                }
                if(d[t]) break;
            }
            if(!d[t]) break;
            for(int i = t; i != s; i = edges[path[i]].src)
            {
                edges[path[i]].flow += d[t];
                edges[path[i]^1].flow -= d[t];
            }
            flow += d[t];
        }
        return flow;
    }
} network;

int main()
{
    int n, m, s, t, x, y, w, kase = 0;
    while(cin >> n && n)
    {
        network.init(n+1);
        cin >> s >> t >> m;
        while(m--)
        {
            cin >> x >> y >> w;
            network.add_edge(x, y, w);
        }
        printf("Network %d\nThe bandwidth is %d.\n\n", ++kase, network.max_flow(s, t));
    }
    return 0;
}
