// UVa 10003 Cutting Sticks
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 55, INF = 0x3fffffff;
int s[maxn], dp[maxn][maxn];

int main()
{
    int x, n, L;
    while (cin >> L && L)
    {
        cin >> n;
        s[0] = 0, s[n+1] = L;
        for (int i = 1; i <= n; i++)
            cin >> s[i];
        for (int i = n; i >= 0; i--)
        {
            dp[i][i+1] = 0;
            for (int j = i+2; j <= n+1; j++)
            {
                dp[i][j] = INF;
                for (int k = i+1; k < j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]+s[j]-s[i]);
            }
        }
        cout << "The minimum cutting is " << dp[0][n+1] << "."<< endl;
    }
    return 0;
}
