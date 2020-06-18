// UVa 1632 Alibaba
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 10005;
const int INF = 0x3fffffff;

// dp[i][j][p] min time to finish range(i, j) and at p (0-i, 1-j)
int n, d[maxn], t[maxn], dp[maxn][maxn][2]; 

int main()
{
    while (cin >> n && n)
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++)
            cin >> d[i] >> t[i];
        for (int i = n-1; i >= 0; i--)
            for (int j = i+1; j < n; j++)
            {
                dp[i][j][0] = min(dp[i+1][j][0]+d[i+1]-d[i], dp[i+1][j][1]+d[j]-d[i]);
                if (dp[i][j][0] >= t[i]) dp[i][j][0] = INF;
                dp[i][j][1] = min(dp[i][j-1][1]+d[j]-d[j-1], dp[i][j-1][0]+d[j]-d[i]);
                if (dp[i][j][1] >= t[j]) dp[i][j][1] = INF;
            }
        int ans = min(dp[0][n-1][0], dp[0][n-1][1]);
        if (ans == INF) cout << "No solution\n";
        else cout << ans << endl;
    }
    return 0;
}
