// UVa 1660 Cable TV Network
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
    Edge(int s=0, int d=0, int k=0, int f=0): src(s), dst(d), cap(k), flow(f) {}
    bool operator < (const Edge &rhs) const { return src < rhs.src || (src == rhs.src && dst < rhs.dst); }
};

struct Dinic
{
    int s, t, dist[maxn], cur[maxn];    // current curve in G[x], don't visit visited curve
    bool vis[maxn];
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
        edges.push_back(Edge(dst, src, 0, 0));
    }

    bool bfs()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        vis[s] = true;
        dist[s] = 0;
        while(!q.empty())
        {
            int src = q.front(); q.pop();
            for(int i : G[src])
            {
                Edge &e = edges[i];
                if(!vis[e.dst] && e.cap > e.flow)
                {
                    vis[e.dst] = true;
                    dist[e.dst] = dist[src] + 1;
                    q.push(e.dst);
                }
            }
        }
        return vis[t];
    }

    int dfs(int src, int d)
    {
        if(src == t || !d) return d;
        int flow = 0, f;
        for(int &i = cur[src]; i < G[src].size(); i++)
        {
            Edge &e = edges[G[src][i]];
            if(dist[e.dst] == dist[src]+1 && (f = dfs(e.dst, min(d, e.cap-e.flow))) > 0)
            {
                e.flow += f;
                edges[G[src][i]^1].flow -= f;
                flow += f;
                d -= f;
                if(!d) break;
            }
        }
        return flow;
    }

    int min_cut(int s, int t)
    {
        this->s = s;
        this->t = t;
        int cut = 0;
        while(bfs())        // layering graph
        {   // augment all paths in layered graph
            memset(cur, 0, sizeof(cur));
            cut += dfs(s, inf);
        }
        return cut;
    }
} network;

// mincut: split each node to an edge so we can count min# of such edges to be removed that graph be cut into two sets 
int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        int x, y;
        char c;
        network.init(2*n);
        for(int i = 0; i < n; i++)
            network.add_edge(i, i+n, 1); // split each node x to x -> x', cap: 1, each node can only be removed once
        for(int i= 0; i < m; i++)
        {
            while(cin >> c && c != '(');
            cin >> x >> c >> y >> c;
            network.add_edge(x+n, y, inf);  // x' -> y, cap: inf, make sure origin edge won't be "removed"
            network.add_edge(y+n, x, inf);  // y' -> x
        }
        int ans = inf;
        vector<Edge> prev_edges = network.edges;
        // set s to be 0 (can be any node)
        if(!prev_edges.empty())
            prev_edges[0].cap = inf;
        for(int t = 1; t < n; t++)         // iterate each other node as t
        {
            network.edges = prev_edges;    // restore the edges
            network.edges[t<<1].cap = inf; 
            ans = min(ans, network.min_cut(0, t+n));
        }
        cout << (ans == inf ? n : ans) << endl;
    }
    return 0;
}
