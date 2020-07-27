// UVa 753 A Plug for UNIX
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 405, inf = 1e9;
int n, m, k, target[maxn], device[maxn];
// c[i][j] plug i connected with plug j
bool c[maxn][maxn];
vector<string> names;

int ID(const string &s)
{
    for(int i = 0; i < names.size(); i++)
        if(names[i] == s) return i;
    names.push_back(s);
    return names.size() - 1;
}

struct Edge
{
    int src, dst, cap, flow;
    Edge(int s, int d, int k, int f): src(s), dst(d), cap(k), flow(f) {}
};

struct EdmondsKarp
{
    int d[maxn], path[maxn];
    vector<Edge> edges;
    vector<int> G[maxn];    //  edge i->j = edges[G[i][j]]

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
        edges.push_back(Edge(src, dst, cap, 0));    // edges[m]
        edges.push_back(Edge(dst, src, 0, 0));      // edges[m^1]
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        for(;;)
        {
            memset(d, 0, sizeof(d));
            queue<int> q;
            q.push(s);
            d[s] = inf;
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
            if(!d[t]) break;    // no more augmenting path, found maxflow
            for(int x = t; x != s; x = edges[path[x]].src)
            {
                edges[path[x]].flow += d[t];
                edges[path[x]^1].flow -= d[t];
            }
            flow += d[t];
        }
        return flow;
    }
} network;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        names.clear();
        string s1, s2;
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> s1, target[i] = ID(s1);
        cin >> m;
        for(int i = 0; i < m; i++)
            cin >> s1 >> s2, device[i] = ID(s2);
        cin >> k;
        memset(c, 0, sizeof(c));
        for(int i = 0; i < k; i++)
            cin >> s1 >> s2, c[ID(s1)][ID(s2)] = true;
        int V = names.size();
        // use floyd to connect plug nodes, or directly add edges between plug nodes and get maxflow
        for(int k = 0; k < V; k++)      
            for(int i = 0; i < V; i++)
                for(int j = 0; j < V; j++)
                    c[i][j] |= c[i][k] && c[k][j];
        network.init(V+2);   // V - s, V+1 - t
        for(int i = 0; i < m; i++)
            network.add_edge(V, device[i], 1);       // unit weight
        for(int i = 0; i < n; i++)
            network.add_edge(target[i], V+1, 1);     // unit weight
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(c[device[i]][target[j]]) network.add_edge(device[i], target[j], inf);
        int match = network.max_flow(V, V+1);
        cout << m - match << endl;
        if(T) cout << endl;
    }
    return 0;
}
