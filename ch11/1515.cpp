// UVa 1515 Pool construction
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 2505, inf = 1e9;

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

int w, h;
char mat[99][99];

inline int ID(int i, int j) { return i*w + j; }

int main()
{
    int T, d, f, b;
    cin >> T;
    while(T--)
    {
        cin >> w >> h >> d >> f >> b;
        for(int i = 0; i < h; i++)
            cin >> mat[i];
        int cost = 0;
        for(int i = 0; i < h; i++)
        {
            if(mat[i][0] == '.') mat[i][0] = '#', cost += f;
            if(mat[i][w-1] == '.') mat[i][w-1] = '#', cost += f;
        }
        for(int j = 0; j < w; j++)
        {
            if(mat[0][j] == '.') mat[0][j] = '#', cost += f;
            if(mat[h-1][j] == '.') mat[h-1][j] = '#', cost += f;
        }
        network.init(h*w+2);
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
            {
                if(mat[i][j] == '#')
                {   // border glass can't be converted so cap is inf
                    int cap = (i && i != h-1 && j && j != w-1) ? d : inf;
                    network.add_edge(h*w, ID(i, j), cap);
                }
                else
                    network.add_edge(ID(i, j), h*w+1, f);
                if(i) network.add_edge(ID(i,j), ID(i-1,j), b);
                if(j) network.add_edge(ID(i,j), ID(i,j-1), b);
                if(i < h-1) network.add_edge(ID(i,j), ID(i+1,j), b);
                if(j < w-1) network.add_edge(ID(i,j), ID(i,j+1), b);
            }
        cout << cost + network.min_cut(h*w, h*w+1) << endl;
    }
    return 0;
}
