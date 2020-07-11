// UVa 1575 Factors
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef unsigned long long ll;

int p[30];
bool vis[100];
ll N, ans, C[70][70];

void init()
{
    int n = 0;
    for(int i = 2; i < 100; i++) if(!vis[i])
    {
        p[n++] = i;
        for(int j = i*i; j < 100; j+=i) vis[j] = true;
    }
    C[0][0] = 1;
    for(int i = 1; i < 70; i++)
    {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
}
// f(k) = n
// first i-1 primes, with total m count whose product is k, has n plans
// picked x i-1th primes, pick y (<= x) ith prime produce n*C(m+y, y) plans
void dfs(int i, int x, int m, ll k, ll n)
{
    if(n == N) {ans = k; return; }
    if(n > N || i > 20) return;
    ll t = 1;
    for(int y = 1; y <= x; y++)
    {
        t *= p[i];
        if(k >= ans / t) return;
        dfs(i+1, y, m+y, k*t, n*C[m+y][y]);
    }
}

int main()
{
    init();
    while(cin >> N)
    {
        if(N == 1) { printf("1 2\n"); continue; }
        ans = (ll)1 << 63;
        dfs(0, 63, 0, 1, 1);
        printf("%lld %lld\n", N, ans);
    }
    return 0;
}
