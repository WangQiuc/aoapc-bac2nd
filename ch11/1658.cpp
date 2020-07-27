// UVa 1658 Admiral
// wangqc
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;

const int maxn = 2005, inf = 0x3f3f3f3f;

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

    int min_cost_max_flow(int s, int t, int limit)
    {
        int flow = 0, cost = 0;
        while (flow < limit)
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
                    if(e.cap > e.flow && dist[e.dst] > dist[src] + e.cost)
                    {
                        d[e.dst] = min(d[src], e.cap-e.flow);
                        dist[e.dst] = dist[src] + e.cost;
                        path[e.dst] = i;
                        if(!vis[e.dst]) q.push(e.dst), vis[e.dst] = true;
                    }
                }
            }
            if(dist[t] == inf) break;
            d[t] = min(d[t], limit - flow);
            flow += d[t];
            cost += dist[t] * d[t];
            for(int i = t; i != s; i = edges[path[i]].src)
            {
                edges[path[i]].flow += d[t];
                edges[path[i]^1].flow -= d[t];
            }
        }
        return cost;
    }
} network;

int main()
{
    int n, m, x, y, w;
    while(cin >> n >> m && n)
    {
        network.init(n*2-2);
        // s: node 0, t: node i-1, src cap = 2 (2 paths), find out min cost max flow
        // node x (1 ~ i-2) break into x->x' with 1 cap to make sure x->x' can be only used once
        for(int i = 1; i < n-1; i++)
            network.add_edge(i, i+n-1, 1, 0);
        while(m--)
        {
            cin >> x >> y >> w, x--, y--;
            if (x && x != n-1) x += n-1;  // x->x'->y->y', connect x'->y here
            network.add_edge(x, y, 1, w);
        }
        cout << network.min_cost_max_flow(0, n-1, 2) << endl;
    }
    return 0;
}
