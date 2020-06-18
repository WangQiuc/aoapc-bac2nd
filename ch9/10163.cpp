// UVa 10163 Storage Keepers
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, max_safe, p[35], dp[105];

int dp_max_safety()
{
    memset(dp, 0, sizeof(dp));
    dp[0] = INF;
    for (int i = 0; i < m; i++)
        for (int j = n; j >= 0; j--)
            for (int k = 1; k <= min(p[i], j); k++)
                dp[j] = max(dp[j], min(dp[j-k], p[i]/k));
    return max_safe = dp[n];
}

int dp_min_cost()
{
    if (max_safe == 0) return 0;
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < m; i++)
        for (int j = n; j >= 0; j--)
            for (int k = 1; k <= min(p[i]/max_safe, j); k++)
                dp[j] = min(dp[j], dp[j-k]+p[i]);
    return dp[n];
}

int main()
{
    while (cin >> n >> m && n)
    {
        for (int i = 0; i < m; i++)
            cin >> p[i];
        cout << dp_max_safety() << " " << dp_min_cost() << endl;
    }
    return 0;
}
