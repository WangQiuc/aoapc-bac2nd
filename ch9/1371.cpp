// UVa 1371 Period
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 5005, maxm = 55, inf = 0x3f3f3f3f;
char p[maxn], q[maxm];
int n, m, dp[maxn][maxm];

bool valid(int k)
{
    memset(dp, inf, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0; i <= n; i++)
    {
        if(dp[i][m] <= k) dp[i][0] = 0;
        for(int j = 0; j <= m; j++) if(dp[i][j] <= k)
        {
            dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+(p[i+1]!=q[j+1]));
			dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
			dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
        }
    }
    return dp[n][m] <= k;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> (q+1) >> (p+1);
        n = strlen(p+1), m = strlen(q+1);
        int lo = 0, hi = m;
        while(lo < hi)
        {   // find lower bound of valid range
            int x = (lo + hi) >> 1;
            if(valid(x)) hi = x;
            else lo = x+1;
        }
        cout << lo << endl;
    }
    return 0;
}
