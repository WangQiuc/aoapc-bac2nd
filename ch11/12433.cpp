// UVa 12433 Rent a Car
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;
typedef long long ll;

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

    int min_cost_max_flow(int s, int t, ll &cost)
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
            cost += (ll)d[t] * (ll)dist[t];
            for(int i = t; i != s; i = edges[path[i]].src)
            {
                edges[path[i]].flow += d[t];
                edges[path[i]^1].flow -= d[t];
            }
        }
        return flow;
    }
} network;

int main()
{
    int T, N, C, R;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> N >> C >> R;
        network.init(N*2+2);
        int t = N*2+1, sum = 0;
        for(int i = 1; i <= N; i++)
        {
            int r; cin >> r;
            network.add_edge(0, i, r, 0);
            network.add_edge(N+i, t, r, 0);
            if(i < N) network.add_edge(N+i, N+i+1, inf, 0); // car in stock on day i can pass to day i+1
            sum += r;
        }
        for(int i = 1; i <= C; i++)
        {
            int c, p; cin >> c >> p; 
            network.add_edge(0, N+1, c, p);    // give all cars to day 1
        }
        for(int i = 0; i < R; i++)
        {
            int d, s; cin >> d >> s;
            for(int j = 1; j <= N; j++) if(j+d+1 <= N) 
                network.add_edge(j, N+j+d+1, inf, s);    // car take service at day j can return at day j+d+1
        }
        ll min_cost = 0;
        cout << "Case " << kase << ": ";
        if(sum != network.min_cost_max_flow(0, t, min_cost)) cout << "impossible\n";
        else cout << min_cost << endl;
    }
    return 0;
}
