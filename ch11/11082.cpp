// UVa 11082 Matrix Decompressing
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 55, maxv = 19, inf = 1e9;

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

int mat[maxn][maxn];

int main()
{
    int T, R, C, v;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> R >> C;
        network.init(R+C+2);
        int prev = 0;
        for(int i = 1; i <= R; i++)
        {
            cin >> v;
            network.add_edge(0, i, v-prev-C);  // -C: every value in this row -= 1 so range will be [0, 19]
            prev = v;
        }
        prev = 0;
        for(int j = 1; j <= C; j++)
        {
            cin >> v;
            network.add_edge(R+j, R+C+1, v-prev-R); // -R: same as above
            prev = v;
        }
        for(int i = 1; i <= R; i++)
            for(int j = 1; j <= C; j++)
            {
                mat[i][j] = network.edges.size();
                network.add_edge(i, R+j, maxv);
            }
        network.max_flow(0, R+C+1);
        cout << "Matrix " << kase << endl;
        for(int i = 1; i <= R; i++)
        {
            for(int j = 1; j <= C; j++)
                cout << network.edges[mat[i][j]].flow + 1 << " ";  // add 1 back
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
