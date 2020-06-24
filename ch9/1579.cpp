// UVa 1579 Matryoshka
// wangqc
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

const int maxn = 505, inf = 1<<30;
int n, a[maxn], dp[maxn][maxn];
bool vis[maxn];

int merge(int i1, int j1, int i2, int j2)
{
    priority_queue<int> q1, q2;
    for(int i = i1; i <= j1; i++) q1.push(a[i]);
    for(int i = i2; i <= j2; i++) q2.push(a[i]);
    int cnt = 0;
    while(!q1.empty() && !q2.empty())
    {
        cnt++;
        q1.top() > q2.top() ? q1.pop() : q2.pop();
    }
    return cnt;
}

int dfs(int i, int j)
{
    if(dp[i][j] != -1) return dp[i][j];
    int &ans = dp[i][j];
    if(i == j) return ans = 0;
    ans = inf;
    for(int k = i+1; k <= j; k++)
        ans = min(ans, merge(i,k-1,k,j)+dfs(i,k-1)+dfs(k,j));
    return ans;
}

int solve()
{
    int ans = 0, i = 0;
    memset(dp, -1, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    vis[a[0]] = true;
    for(int j = 1; j < n; j++) 
    {
        if(vis[a[j]])
        {   // need to be consecutive from 1 to doll's size
            for(int x = 1; x <= j-i; x++)
                if(!vis[x]) return -1;
            ans += dfs(i, j-1);
            memset(vis, 0, sizeof(vis));
            vis[a[j]] = true;
            i = j;
        }
        else vis[a[j]] = true;
    }
    for(int x = 1; x <= n-i; x++)
        if(!vis[x]) return -1;
    return ans + dfs(i, n-1);
}

int main()
{
    while(cin >> n)
    {
        for(int i = 0; i < n; i++) cin >> a[i];
        int ans = solve(); 
        if (ans == -1) cout << "impossible\n";
        else cout << ans << endl;
    }
    return 0;
}
