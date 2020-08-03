// UVa 11671 Sign of Matrix
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;
const int maxn = 205;
struct Edge
{
    int s, d, w;
    Edge(int s, int d, int w): s(s), d(d), w(w) {}
};

int n, m, dist[maxn], a[maxn];
bool vis[maxn];
vector<Edge> edges;
vector<int> G[maxn];

void add_edge(int s, int d, int w)
{
    G[s].push_back(edges.size());
    edges.push_back(Edge(s, d, w));
}

bool solve()
{
    queue<int> q;
    for(int i = 0; i < m; i++)
    {
        q.push(i);
        vis[i] = true;
        dist[i] = 0;
        a[i] = 1;
    }
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        vis[x] = false;
        for(int i : G[x])
        {
            Edge &e = edges[i];
            if(dist[e.d] > dist[x] + e.w)
            {
                dist[e.d] = dist[x] + e.w;
                if(!vis[e.d])
                {
                    q.push(e.d);
                    vis[e.d] = true;
                    a[e.d]++;
                    if(a[e.d] > n*2+1) return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int kase = 0;
    while(cin >> n && n != -1)
    {
        m = n<<1;
        memset(dist, 0, sizeof(int)*m);
        memset(a, 0, sizeof(int)*m);
        memset(vis, 0, sizeof(int)*m);
        edges.clear();
        for(int i = 0; i < m; i++) 
            G[i].clear();
        for(int i = 0; i < n; i++)
        {
            string s; cin >> s;
            for(int j = 0; j < n; j++)
            {
                if(s[j] == '+') add_edge(i, j+n, -1);
                else if(s[j] == '-') add_edge(j+n, i, -1);
                else 
                {
                    add_edge(i, j+n, 0);
                    add_edge(j+n, i, 0);
                }
            }
        }
        int ans = 0;
        if(solve())
        {
            sort(dist, dist+m);
            for(int i = 0; i < m; i++)
                ans += abs(dist[i] - dist[n-1]);
        }
        else ans = -1;
        cout << "Case " << ++kase << ": " << ans << endl;
        
    }
    return 0;
}
