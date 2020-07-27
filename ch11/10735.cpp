// UVa 10735 Euler Circuit
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 105, maxm = 505, inf = 1e9;

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
        edges.push_back(Edge(dst, src, 0, 0));
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

int n, m, x[maxm], y[maxm], dir[maxm], id[maxm], diff[maxm];
vector<int> G[maxn], path;
vector<bool> vis[maxn];

void euler(int u)
{
    for(int i = 0; i < G[u].size(); i++) if(!vis[u][i])
    {
        vis[u][i] = true;
        euler(G[u][i]);
        path.push_back(G[u][i]+1);
    }
}

void print()
{
    for(int i = 0; i < n; i++)
        G[i].clear(), vis[i].clear();
    for(int i = 0; i < m; i++)
    {
        bool rev = false;
        if(!dir[i] && network.edges[id[i]].flow > 0) rev = true;
        if(!rev) G[x[i]].push_back(y[i]), vis[x[i]].push_back(false);
        else G[y[i]].push_back(x[i]), vis[y[i]].push_back(false);
    }
    path.clear();
    euler(0);
    cout << 1;
    for(int i = path.size()-1; i >= 0; i--)
        printf(" %d", path[i]);
    cout << endl;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m;
        network.init(n+2);
        memset(diff, 0, sizeof(diff));
        for(int i = 0; i < m; i++)
        {
            char s[5];
            cin >> x[i] >> y[i] >> s;
            x[i]--, y[i]--;
            dir[i] = (s[0] == 'D');
            diff[x[i]]++;
            diff[y[i]]--;
            if(!dir[i])
            {
                id[i] = network.edges.size();
                network.add_edge(x[i], y[i], 1);
            }
        }
        bool ok = true;
        for(int i = 0; i < n; i++)
            if(diff[i] & 1)
            {   ok = false; break; }
        int s = n, t = n+1;
        if(ok)
        {
            int sum = 0;
            for(int i = 0; i < n; i++)
            {
                if(diff[i] > 0)
                    network.add_edge(s, i, diff[i]>>1), sum += diff[i]>>1;
                if(diff[i] < 0)
                    network.add_edge(i,t, -diff[i]>>1);
            }
            if(network.max_flow(s, t) != sum) ok = false;
        }
        if(!ok) cout << "No euler circuit exists\n";
        else print();
        if(T) cout << endl;
    }
    return 0;
}
