// UVa 1336 Fixing the Great Wall
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<cassert>
#include<algorithm>

using namespace std;

const int maxn = 1005;
const double INF = 1e30;

struct Node
{
    double x, c, d;
    bool operator < (const Node &rhs) const { return x < rhs.x; }
} nodes[maxn];

int kase, n, vis[maxn][maxn][2];
double v, x, psum[maxn], dp[maxn][maxn][2];

double cost(double x1, double x2, int i, int j)
{
    assert(i <= j);
    double c = (i >= 0 && j >= 0) ? psum[j] - psum[i-1] : 0;
    return (psum[n] - c) * fabs(x1-x2) / v;
}

double dfs(int i, int j, int p)  // p-0 left, p-1 right
{
    if (i == 1 && j == n) return 0;
    double &ans = dp[i][j][p];
    if (vis[i][j][p] == kase) return ans;
    vis[i][j][p] = kase;
    ans = INF;
    double x = p ? nodes[j].x : nodes[i].x;
    if (i > 1) ans = min(ans, dfs(i-1,j,0) + cost(x, nodes[i-1].x, i, j));
    if (j < n) ans = min(ans, dfs(i,j+1,1) + cost(x, nodes[j+1].x, i, j));
    return ans;
}

int main()
{
    memset(vis, 0, sizeof(vis));
    while (cin >> n >> v >> x && n)
    {
        ++kase;
        double sumc = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> nodes[i].x >> nodes[i].c >> nodes[i].d;
            sumc += nodes[i].c;
        }
        sort(nodes+1, nodes+n+1);
        psum[0] = 0;
        for (int i = 1; i <= n; i++)
            psum[i] = psum[i-1] + nodes[i].d;
        nodes[0].x = -INF, nodes[n+1].x = INF;
        double ans = INF;
        for (int i = 1; i <= n+1; i++) if (x > nodes[i-1].x && x < nodes[i].x)
        {
            if (i > 1) ans = min(ans, dfs(i-1,i-1,0) + cost(x, nodes[i-1].x, -1, -1));
            if (i <= n) ans = min(ans, dfs(i,i,0) + cost(x, nodes[i].x, -1, -1));
            break;
        }
        printf("%.0lf\n", floor(ans + sumc));
    }
    return 0;
}
