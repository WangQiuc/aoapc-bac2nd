// UVa 1628 Pizza Delivery
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 105;

int kase, n;
int p[maxn], v[maxn], d[maxn][maxn][maxn][2], vis[maxn][maxn][maxn][2];


// already cover [i, j], k customer to delivery, current at i(r-0) or j(r-1)
int dp(int i, int j, int k, int r)
{
    if (k == 0) return 0;
    int &ans = d[i][j][k][r];
    if (vis[i][j][k][r] == kase) return ans;
    vis[i][j][k][r] = kase;
    ans = 0;
    if (!r) // p is at i, all rest k add p[x]-p[i] penalty
    {
        for (int x = 0; x < i; x++)
            ans = max(ans, v[x]-abs(p[x]-p[i])*k + dp(x,j,k-1,0));
        for (int x = j+1; x < n; x++)
            ans = max(ans, v[x]-abs(p[x]-p[i])*k + dp(i,x,k-1,1));
    }
    else    // p is at j, all rest k add p[x]-p[j] penalty
    {
        for (int x = 0; x < i; x++) 
            ans = max(ans, v[x]-abs(p[x]-p[j])*k + dp(x,j,k-1,0));
        for (int x = j+1; x < n; x++) 
            ans = max(ans, v[x]-abs(p[x]-p[j])*k + dp(i,x,k-1,1));
    }
    return ans;
}


int main()
{
    int T;
    cin >> T;
    memset(vis, 0, sizeof(vis));
    for (kase = 1; kase <= T; kase++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> v[i];
        int ans = 0;
        // delivery k customers, go to deliver i first
        for (int k = 1; k <= n; k++)
            for (int i = 0; i < n; i++)
                ans = max(ans, v[i]-k*abs(p[i])+dp(i,i,k-1,0));
        cout << ans << endl;
    }
    return 0;
}
