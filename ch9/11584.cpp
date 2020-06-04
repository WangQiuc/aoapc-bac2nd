// UVa 11584 Partitioning by Palindromes
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1005;
int n, kase, vis[maxn][maxn], dp[maxn];  // dp[i] minimum palidrome # in s[:i]
bool p[maxn][maxn];
char s[maxn];

bool is_palidrome(int i, int j)     // s[i:j+1] is palidrome
{
    if (i >= j) return true;
    if (s[i] != s[j]) return false;
    if (vis[i][j] != kase)
        vis[i][j] = kase, p[i][j] = is_palidrome(i+1, j-1);
    return p[i][j];
}

int main()
{
    int T;
    cin >> T;
    memset(vis, 0, sizeof(vis));
    for (kase = 1; kase <= T; kase++)
    {
        cin >> s;
        int n = strlen(s);
        for (int j = 0; j <= n; j++)
        {
            dp[j] = j;
            for (int i = 0; i < j; i++)
                if (is_palidrome(i, j-1)) dp[j] = min(dp[j], dp[i]+1);
        }
        cout << dp[n] << endl;
    }
    return 0;
}
