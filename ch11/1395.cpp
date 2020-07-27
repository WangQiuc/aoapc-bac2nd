// UVa 1395 Slim Span
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 105, inf = 0x3fffffff;
int n, P[maxn];
int find(int x) { return x == P[x] ? x : (P[x] = find(P[x])); }

struct Edge
{
    int x, y, w;
    Edge(int x, int y, int w):x(x), y(y), w(w) {}
    bool operator < (const Edge &rhs) const { return w < rhs.w; };
};
vector<Edge> e;

int solve()
{
    int m = e.size();
    sort(e.begin(), e.end());
    int ans = inf;
    for(int L = 0; L < m; L++)
    {
        for(int i = 1; i <= n; i++) P[i] = i;
        int cnt = n;
        for(int R = L; R < m; R++)
        {
            int px = find(e[R].x), py = find(e[R].y);
            if((px == py)) continue;
            P[py] = px;
            if(--cnt == 1) { ans = min(ans, e[R].w - e[L].w); break; }
        }
    }
    return ans == inf ? -1 : ans;
}

int main()
{
    int m, x, y, w;
    while(cin >> n >> m && n)
    {
        e.clear();
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> w;
            e.push_back(Edge(x, y, w));
        }
        cout << solve() << endl;
    }
    return 0;
}
