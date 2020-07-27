// UVa 1659 Help Little Laura
// wangqc
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

using namespace std;

const int maxn = 105, inf = 1e9;

struct Edge
{
    int src, dst, cap, flow;
    double cost;
    Edge(int s, int d, int k, int f, double w): src(s), dst(d), cap(k), flow(f), cost(w) {}
};

struct MCMF     // min cost max flow
{
    int d[maxn], path[maxn];
    double dist[maxn];
    bool vis[maxn];
    vector<Edge> edges;
    vector<int> G[maxn];

    void init(int n)
    {
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void add_edge(int src, int dst, int cap, double cost)
    {
        int m = edges.size();
        G[src].push_back(m);
        G[dst].push_back(m^1);
        edges.push_back(Edge(src, dst, cap, 0, cost));
        edges.push_back(Edge(dst, src, 0, 0, -cost));
    }

    double min_cost_max_flow(int s, int t)
    {
        int flow = 0;
        double cost = 0;
        for(;;)
        {
            for(int i = 0; i < maxn; i++) dist[i] = inf;
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
        return cost;
    }
} network;

int x[maxn], y[maxn], c1[maxn], c2[maxn];
vector<int> G[maxn];

int main()
{
    int n, a, b, kase = 0;
    while(cin >> n >> a >> b)
    {
        network.init(n+2);
        for(int i = 0, j; i < n; i++)
        {
            cin >> x[i] >> y[i];
            G[i].clear();
            while(cin >> j && j)
                G[i].push_back(j-1);
        }
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        double sum = 0;
        for(int i = 0; i < n; i++)
            for(int j : G[i])
            {
                double d = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                double edge_cost = -d*a+b;
                if(edge_cost >= 0)
                    network.add_edge(i, j, 1, edge_cost);
                else
                {
                    network.add_edge(j, i, 1, -edge_cost);
                    c1[j]++, c2[i]++;
                    sum -= edge_cost;
                }
            }
        for(int i = 0; i < n; i++)
        {
            if(c1[i] > c2[i]) network.add_edge(n, i, c1[i]-c2[i], 0);
            if(c2[i] > c1[i]) network.add_edge(i, n+1, c2[i]-c1[i], 0);
        }
        printf("Case %d: %.2lf\n", ++kase, max(sum - network.min_cost_max_flow(n, n+1), 0.0));
    }
    return 0;
}