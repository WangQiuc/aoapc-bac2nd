// UVa 1349 Optimal Bus Route Design
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 205, inf = 0x3f3f3f3f;

struct Edge
{
    int src, dst, cap, flow, cost;
    Edge(int s, int d, int k, int f, int w): src(s), dst(d), cap(k), flow(f), cost(w) {}
};

struct MCMF     // min cost max flow
{
    int d[maxn], path[maxn], dist[maxn];
    bool vis[maxn];
    vector<Edge> edges;
    vector<int> G[maxn];

    void init(int n)
    {
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void add_edge(int src, int dst, int cap, int cost)
    {
        int m = edges.size();
        G[src].push_back(m);
        G[dst].push_back(m^1);
        edges.push_back(Edge(src, dst, cap, 0, cost));
        edges.push_back(Edge(dst, src, 0, 0, -cost));
    }

    int min_cost_max_flow(int s, int t, int &cost)
    {
        int flow = 0;
        for(;;)
        {
            memset(dist, inf, sizeof(dist));
            memset(vis, 0, sizeof(vis));
            dist[s] = 0, vis[s] = true, path[s] = 0, d[s] = inf;
            queue<int> q;
            q.push(s);
            while(!q.empty())
            {
                int src = q.front(); q.pop();
                vis[src] = false;
                for(int i : G[src])
                {
                    Edge &e = edges[i];
                    if(e.cap > e.flow && dist[e.dst] > dist[src]+e.cost)
                    {
                        d[e.dst] = min(d[src], e.cap-e.flow);
                        path[e.dst] = i;
                        dist[e.dst] = dist[src]+e.cost;
                        if(!vis[e.dst]) q.push(e.dst), vis[e.dst] = true;
                    }
                }
            }
            if(dist[t] == inf) break;
            flow += d[t];
            cost += d[t] * dist[t];
            for(int i = t; i != s; i = edges[path[i]].src)
            {
                edges[path[i]].flow += d[t];
                edges[path[i]^1].flow -= d[t];
            }
        }
        return flow;
    }
} network;

// bipartite matching: each node u split into ux(x), uy(n+x)
// for route u->v: ux->vy, so every x should match exactly one y
int main()
{
    int n, m, d;
    while(cin >> n && n)
    {
        network.init(n*2+2);
        for(int x = 1; x <= n; x++)
        {
            network.add_edge(0, x, 1, 0);           // s -> x
            network.add_edge(n+x, n*2+1, 1, 0);     // y -> t
        }
        for(int i = 1; i <= n; i++)
        {
            for(;;)
            {
                int j;
                cin >> j;
                if(!j) break;
                cin >> d;
                network.add_edge(i, n+j, 1, d);     // ix -> jy with cost d
            }
        }
        int cost = 0;
        int flow = network.min_cost_max_flow(0, 2*n+1, cost);
        if(flow < n) cout << "N\n";
        else cout << cost << endl;
    }
    return 0;
}
