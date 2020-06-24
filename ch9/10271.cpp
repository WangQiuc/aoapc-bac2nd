// UVa 10271 Chopsticks
// wangqc
#include<iostream>

using namespace std;

const int maxn = 5005, inf = 1<<30;
int a[maxn], dp[maxn][maxn];

int main()
{
    int n, k, T;
    cin >> T;
    while(T--)
    {
        cin >> k >> n;
        k += 8;
        for(int i = n; i > 0; i--)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            for (int j = 1; j <= k; j++)
                dp[i][j] = inf;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= k; j++)
                if (i >= j*3) dp[i][j] = min(dp[i-1][j], dp[i-2][j-1]+(a[i-1]-a[i])*(a[i-1]-a[i]));
        cout << dp[n][k] << endl;
    }
    return 0;
}
