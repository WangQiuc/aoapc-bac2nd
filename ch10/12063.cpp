// UVa 12063 Zeros and Ones
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;
const int maxn = 70, maxk = 100;
int n, M[maxn+10];
ll k, d[maxn+10][maxn*2+10][maxk+10];

void gen_M()
{
    M[1] = 1;
    for(int i = 2; i <= n; i++)
        M[i] = (M[i-1] << 1) % k;
}

// M[i] = (1<<i) % k, v % k = m, (1<<i) % k + (v-(1<<i)) % k = m, (v-(1<<i)) % k = m-M[i]
// dp(i, x, m), first i bits contain x '1', who % k = m
// dp(i, x, m) = dp(i-1, x, m) + dp(i-1, x-1, m-M[i]), ith bit is 0 or 1
ll dp(int i, int x, int m)
{
    if(i == 0) return x ? 0 : d[i][x][m] = !m; // if m is 0, dp return 1
    if(d[i][x][m] != -1) return d[i][x][m];
    ll &ans = d[i][x][m];
    ans = dp(i-1, x, m);
    if(x) ans += dp(i-1, x-1, (m-M[i]+k)%k);
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        memset(d, -1, sizeof(d));
        cin >> n >> k;
        if(k==0 || (n&1)) printf("Case %d: 0\n", kase);
        else { gen_M(); printf("Case %d: %lld\n", kase, dp(n-1, (n-1)>>1, (k-M[n])%k)); }
    }
    return 0;
}
