// UVa 10837 A Research Problem
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn = 10005, inf = 200000000;
int m, ans, p[maxn], a[maxn], np, na;
bool vis[maxn];

void init()
{
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        p[np++] = i;
        for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    }
}

void get_factor()
{
    na = 0;
    int n = sqrt(m+0.5);
    for(int i = 0; i < np && p[i]-1 <= n; i++)
        if(m % (p[i]-1) == 0) a[na++] = p[i];
}

bool valid(int x)
{
    int n = sqrt(x+0.5);
    for(int i = 0; i < np && p[i] <= n; i++)
        if(x % p[i] == 0) return false;
    for(int i = 0; i < na; i++)
        if(a[i] == x && vis[i]) return false;
    return true;
}

// φ(n) = n*∏(1-1/pi) = n*∏((pi-1)/pi), φ(n) % (pi-1) == 0
// ith factor, current n, φ value f left
void dfs(int i, int f, int n)
{
    if(i == na)
    {
        if(f == 1) ans = min(ans, n);
        else if(valid(f+1)) ans = min(ans, n*(f+1));
        return;
    }
    dfs(i+1, f, n); // not use ith factor
    if(f % (a[i]-1)) return;
    vis[i] = true;
    f /= (a[i]-1), n *= a[i], dfs(i+1, f, n);
    while(f % a[i] == 0)
        f /= a[i], n *= a[i], dfs(i+1, f, n);
    vis[i] = false;
}

int main()
{
    init();
    int kase = 0;
    while(cin >> m && m)
    {
        get_factor();
        ans = inf;
        memset(vis, 0, sizeof(vis));
        dfs(0, m, 1);
        printf("Case %d: %d %d\n", ++kase, m, ans);
    }
    return 0;
}
