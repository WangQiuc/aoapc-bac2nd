// UVa 1380 A Scheduling Problem
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 205;
const int INF = 1000000000;
// f min_d from x to its leaf, g=min_d from x's leaf to x
int n, root, maxlen, f[maxn], g[maxn];
bool is_root[maxn];

struct Edge
{
    int y, d;
    Edge(int y=0, int d=0): y(y), d(d) {}
};

struct Unode
{
    int x, f, g;
    Unode(int x=0, int f=0, int g=0): x(x), f(f), g(g) {}
};

bool cmp_f(const Unode &u1, const Unode &u2) { return u1.f < u2.f; }

bool cmp_g(const Unode &u1, const Unode &u2) { return u1.g < u2.g; }

vector<Edge> graph[maxn];

int dfs(int x)
{
    int ans = 0;
    for (Edge e : graph[x]) if (e.d == 1)
        ans = max(ans, dfs(e.y)+1);
    return ans;
}

bool read_data()
{
    bool ok = false;
    int x, y;
    n = 0;
    for (int i = 0; i < maxn; i++) graph[i].clear();
    memset(is_root, 1, sizeof(is_root));
    while (cin >> x && x)
    {
        ok = true;
        string s;
        n = max(n, x);
        while (cin >> s && s != "0")
        {
            int len = s.length();
            char dir = s[len-1];
            if (dir == 'd' || dir == 'u') s = s.substr(0, len-1);
            stringstream ss(s);
            ss >> y;
            n = max(n, y);
            is_root[y] = false;
            if (dir == 'd')
            {
                graph[x].push_back(Edge(y, 1));
                graph[y].push_back(Edge(x, 2));
            }
            else if (dir == 'u')
            {
                graph[x].push_back(Edge(y, 2));
                graph[y].push_back(Edge(x, 1));  
            }
            else 
                graph[x].push_back(Edge(y, 0));
        }
    }
    if (ok) for (int i = 1; i <= n; i++)
        if (is_root[i] && !graph[i].empty()) { root = i; break; }
    return ok;
}
bool dp(int x, int p)
{
    if (graph[x].empty())
    {
        f[x] = g[x] = 0;
        return true;
    }
    vector<Unode> children;
    int f0 = 0, g0 = 0;
    for (Edge e : graph[x])
    {
        if (e.y == p) continue;
        dp(e.y, x);
        if (e.d == 1) g0 = max(g0, g[e.y]+1);
        else if (e.d == 2) f0 = max(f0, f[e.y]+1);
        else children.push_back(Unode(e.y, f[e.y], g[e.y]));
    }
    if (children.empty())
    {
        f[x] = f0, g[x] = g0;
        if (f[x] + g[x] > maxlen) f[x] = g[x] = INF;
        return f[x] < INF;
    }
    f[x] = g[x] = INF;
    int m = children.size();
    sort(children.begin(), children.end(), cmp_f);
    int maxg[maxn];
    maxg[m-1] = children[m-1].g;
    for (int k = m-2; k >= 0; k--)
        maxg[k] = max(children[k].g, maxg[k+1]);
    for (int k = 0; k <= m; k++)
    {
        int ff = f0, gg = g0;
        if (k > 0) ff = max(ff, children[k-1].f + 1);
        if (k < m) gg = max(gg, maxg[k] + 1);
        if (ff + gg <= maxlen) f[x] = min(f[x], ff);
    }
    sort(children.begin(), children.end(), cmp_g);
    int maxf[maxn];
    maxf[m-1] = children[m-1].f;
    for (int k = m-2; k >= 0; k--)
        maxf[k] = max(children[k].f, maxf[k+1]);
    for (int k = 0; k <= m; k++)
    {
        int ff = f0, gg = g0;
        if (k > 0) gg = max(gg, children[k-1].g + 1);
        if (k < m) ff = max(ff, maxf[k] + 1);
        if (ff + gg <= maxlen) g[x] = min(g[x], gg);
    }
    return f[x] < INF;
}

int main()
{
    while(read_data())
    {
        maxlen = 0;
        for (int i = 1; i <= n; i++)
            maxlen = max(maxlen, dfs(i));
        if (dp(root, -1)) cout << maxlen + 1 << endl;
        else cout << maxlen + 2 << endl;
    }
    return 0;
}
