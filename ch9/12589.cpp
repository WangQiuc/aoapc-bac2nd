// UVa 12589 Learning Vector
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 55, maxh = maxn * maxn;
const int inf = 1<<30;
int n, k, kase, d[maxn][maxn][maxh], vis[maxn][maxn][maxh];
struct Vector
{
    int x, y;
    bool operator < (const Vector &rhs) const { return y * rhs.x > rhs.y * x; }
} V[maxn];

// read ith vector, select x of them, accumulate height h
int dp(int i, int x, int h)
{
    if (x == k) return 0;
    if (i == n) return -inf;
    int &ans = d[i][x][h];
    if (vis[i][x][h] == kase) return ans;
    vis[i][x][h] = kase;
    return ans = max(dp(i+1, x, h), dp(i+1, x+1, h+V[i].y) + V[i].x*(2*h+V[i].y));
}

int main()
{
    int T;
    cin >> T;
    memset(vis, 0, sizeof(vis));
    for (kase = 1; kase <= T; kase++)
    {
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> V[i].x >> V[i].y;
        sort(V, V+n);
        cout << "Case " << kase << ": " << dp(0, 0, 0) << endl;
    }
    return 0;
}
