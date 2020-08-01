// UVa 12264 Risk
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 105, inf = 1e9;
int n, a[maxn];
char mat[maxn][maxn];

struct Edge
{
    int src, dst, cap, flow;
    Edge(int s=0, int d=0, int k=0, int f=0): src(s), dst(d), cap(k), flow(f) {}
    bool operator < (const Edge &rhs) const { return src < rhs.src || (src == rhs.src && dst < rhs.dst); }
};

struct Dinic
{
    int s, t, dist[maxn<<1], cur[maxn<<1];    // current curve in G[x], don't visit visited curve
    bool vis[maxn<<1];
    vector<Edge> edges;
    vector<int> G[maxn<<1];
    
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
            if(dist[e.dst] == dist[src] + 1 && (f = dfs(e.dst, min(d, e.cap-e.flow))) > 0)
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

    int max_flow(int s, int t)
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


int build(int val)
{
    int sum = 0;
    network.init(2*n+2);
    for(int i = 1; i <= n; i++)
    {
        bool border = false;
        if(!a[i]) continue;
        network.add_edge(0, i, a[i]);
        network.add_edge(i, i+n, a[i]);     // breakpoint, undirected network flow
        for(int j = 1; j <= n; j++) if(mat[i][j] == 'Y')
        {
            if(!a[j]) border = true;
            else network.add_edge(i, j+n, inf);
        }
        int tval = border ? val : 1;
        network.add_edge(i+n, 2*n+1, tval);
        sum += tval;
    }
    return sum;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        int l = 0, r = 0;
        for(int i = 1; i <= n; i++)
            cin >> a[i], r += a[i];
        for(int i = 1; i <= n; i++)
            cin >> mat[i]+1;
        while(l < r)
        {
            int m = (l+r+1)>>1;
            if(build(m) == network.max_flow(0, 2*n+1))
                l = m;
            else
                r = m-1;
        }
        cout << l << endl;
    }
    return 0;
}
