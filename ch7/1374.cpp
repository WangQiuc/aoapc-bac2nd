// UVa 1374 Power Calculus
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
const int maxn = 20;
int n, a[maxn];
bool vis[2000]; 

// no way to reach n within t times if (maxv << t) < n
int maxv(int d)
{
    int maxv = a[0];
    for (int i = 1; i <= d; i++) maxv = max(maxv, a[i]);
    return maxv;
}

bool dfs(int d, int maxd)
{
    if (a[d] == n) return true;
    if (d == maxd || vis[a[d]] || (maxv(d) << (maxd - d)) < n) return false;
    vis[a[d]] = true;
    // a[d+1] must be generated by a[d], otherwise if a[d+1] = a[d'] + a[i], d' < d
    // then dfs should return at previous search as d'th iteration (d' < d) 
    for (int i = d; i >= 0; i--) 
    {
        a[d+1] = a[d] + a[i];
        if (dfs(d+1, maxd)) return true;
        a[d+1] = a[d] - a[d-i];
        if (a[d+1] > 0 && dfs(d+1, maxd)) return true;
    }
    vis[a[d]] = false;
    return false;
}

int solve(int n)
{
    memset(vis, 0, sizeof(vis));
    for (int maxd = 0; maxd < maxn; maxd++)
        if (dfs(0, maxd)) return maxd;
    return maxn;
}

int main()
{
    a[0] = 1;
    while (cin >> n && n)
        cout << solve(n) << endl;;
    return 0;
}