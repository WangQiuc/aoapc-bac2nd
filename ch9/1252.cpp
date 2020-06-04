// UVa 1252 Twenty Questions
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 128, maxm = 11;
int kase, n, m;
char buf[maxn][maxm + 10];
int vis[1<<maxm][1<<maxm], d[1<<maxm][1<<maxm], cnt[1<<maxm][1<<maxm];

void init()
{
    for (int s = 0; s < (1<<m); s++)
    {
        for (int a = s; a; a = (a-1)&s)     // enumerate all subset of s
            cnt[s][a] = 0;
        cnt[s][0] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        int features = 0;
        for (int f = 0; f < m; f++) if (buf[i][f] == '1')
            features |= 1 << f;
        for (int s = 0; s < (1<<m); s++)
            cnt[s][s&features]++;     // object # that fits (s, a)
    }     

}

int dp(int s, int a)
{
    if (cnt[s][a] <= 1) return 0;
    if (cnt[s][a] == 2) return 1;
    int &ans = d[s][a];
    if (vis[s][a] == kase) return ans;
    vis[s][a] = kase;
    ans = m;
    for (int k = 0; k < m; k++) if (!(s&(1<<k)))
    {
        int s2 = s|(1<<k), a2 = a|(1<<k);
        if (cnt[s2][a2] >= 1 && cnt[s2][a] >= 1)
            ans = min(ans, max(dp(s2, a), dp(s2, a2)) + 1);
    }
    return ans;
}

int main()
{
    memset(vis, 0, sizeof(vis));
    while (cin >> m >> n && n)
    {
        kase++;
        for (int i = 0; i < n; i++) 
            cin >> buf[i];
        init();
        cout << dp(0, 0) << endl;
    }
    return 0;
}
