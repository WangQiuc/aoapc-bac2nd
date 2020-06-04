// UVa 12563 Jin Ge Jin Qu hao
// wangqc
#include<iostream>

using namespace std;

const int maxn = 55;
const int INF = 0x3fffffff;
int n, t, W[maxn], dp[2][maxn*180+700];

int main()
{
    int ans, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> n >> t;
        for (int i = 0; i < n; i++) cin >> W[i];
        for (int i = 0; i < t; i++) dp[0][i] = -1;
        dp[0][0] = ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < t; j++)
            {
                dp[(i+1)&1][j] = dp[i&1][j];
                if (j >= W[i] && dp[i&1][j-W[i]] >= 0)
                    dp[(i+1)&1][j] = max(dp[(i+1)&1][j], dp[i&1][j-W[i]] + 1);
                ans = max(ans, dp[(i+1)&1][j]);
            }
        for (int j = t-1; j >= 0; j--) if (dp[n&1][j] == ans)
        {
            cout << "Case " << kase << ": " << ans+1 << " " << j+678 << endl;
            break;
        }
    }
    return 0;
}
