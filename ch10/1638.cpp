// UVa 1638 Pole Arrangement
// wangqc
#include<iostream>

using namespace std;

const int maxn = 20;
// dp[i][j][k] ranked i poles, can see j poles from left and k poles from right
// dp[i][j][k] = dp[i-1][j-1][k] + dp[i-1][j][k-1] + (i-2)*dp[i-1][j][k]
long long d[maxn+1][maxn+1][maxn+1];

int main()
{
    d[1][1][1] = 1;
    for(int i = 2; i <= maxn; i++)
        for(int j = 1; j <= maxn; j++)
            for(int k = 1; k <= maxn; k++)
            {
                d[i][j][k] = d[i-1][j][k] * (i-2);
                if(j > 1) d[i][j][k] += d[i-1][j-1][k];
                if(k > 1) d[i][j][k] += d[i-1][j][k-1];
            }
    int T, n, L, R;
    cin >> T;
    while(T--)
    {
        cin >> n >> L >> R;
        cout << d[n][L][R] << endl;
    }
    return 0;
}
