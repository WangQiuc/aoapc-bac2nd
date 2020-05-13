// UVa 524 Prime Ring Problem
// wangqc
#include<iostream>
#include<cstring>

const int maxn = 40;
int n, A[maxn];
bool isp[maxn], vis[maxn];

using namespace std;

bool is_prime(int x)
{
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

void dfs(int cur)
{
    if (cur == n && isp[A[0] + A[n-1]])
    {
        for (int i = 0; i < n; i++) 
        {
            if (i) cout << " ";
            cout << A[i];
        }
        cout << endl;
    }
    else for (int i = 2; i <= n; i++)
    {
        if (!vis[i] && isp[i + A[cur-1]])
        {
            A[cur] = i; 
            vis[i] = true;
            dfs(cur + 1);
            vis[i] = false;
        }
    }
}

int main()
{
    int kase = 0;
    for (int i = 2; i < maxn; i++) isp[i] = is_prime(i);
    while (cin >> n && n)
    {
        if (kase++) cout << endl;
        cout << "Case " << kase << ":\n";
        memset(vis, 0, sizeof (vis));
        A[0] = 1;
        dfs(1);
    }
    return 0;
} 
