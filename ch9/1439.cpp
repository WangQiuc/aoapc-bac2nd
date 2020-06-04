// UVa 1439 Exclusive Access 2
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 15;
const int maxm = 105;
int n, m, x[maxn], y[maxn], color[maxn], d[1<<maxn], path[1<<maxn];
bool G[maxn][maxn], ok[1<<maxn];    // ok[s] set s is independent 

bool independent(int s)
{
    for (int i = 0; i < maxn; i++) if (s & (1<<i))
        for (int j = 0; j < maxn; j++) if (s & (1<<j))
            if (i != j && G[i][j]) return false;
    return true;
}

// min color needed to set subset s0
int dp(int s0)
{
    if (s0 == 0) return 0;
    int &ans = d[s0];
    if (ans < 0)
    {
        ans = maxn + 1;
        for (int s = s0; s; s = (s-1)&s0) if(ok[s])
        {
            int v = dp(s^s0) + 1;
            if (v < ans) ans = v, path[s0] = s;
        }
    }
    return ans;
}

void mark(int s, int c)
{
    for (int i = 0; i < maxn; i++)
        if (s & (1<<i)) color[i] = c;
}

int main()
{
    while (cin >> m)
    {
        memset(G, 0, sizeof(G));
        int s0 = 0;
        for (int i = 0; i < m; i++)
        {
            char r1[5], r2[5];
            cin >> r1 >> r2;
            x[i] = r1[0] - 'L', y[i] = r2[0] - 'L';
            G[x[i]][y[i]] = true;
            s0 |= (1 << x[i]) | (1 << y[i]);
        }
        memset(ok, 0, sizeof(ok));
        for (int s = s0; s; s = (s-1)&s0)
            if (independent(s)) ok[s] = true;
        memset(d, -1, sizeof(d));
        int ans = dp(s0);
        cout << ans - 2 << endl;
        int k = 0;
        while (s0)
        {
            mark(s0, k++);
            s0 ^= path[s0];
        }
        for (int i = 0; i < m; i++)
        {
            if (color[x[i]] < color[y[i]]) swap(x[i], y[i]);
            printf("%c %c\n", x[i]+'L', y[i]+'L');
        }
    }
    return 0;
}
