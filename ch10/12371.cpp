// UVa 12371 Guards
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

const ll maxn= 1e5, M = 1e9 + 7;
ll dp[maxn+5][55];

void init()
{
    memset(dp, 0, sizeof(dp));
    dp[2][1] = 1;
    for(int i = 3; i <= maxn; i++)
        for(int j = 1; j <= 50 && j <= i; j++)
            dp[i][j] = (dp[i-1][j]*(i-1)%M*(i-1)%M + dp[i-1][j]*(i-1)%M + dp[i-2][j-1]*((ll)i*(i-1)/2)%M*(i-1)%M) % M;
}

int main()
{
    int T;
    cin >> T;
    init();
    for(int kase = 1; kase <= T; kase++)
    {
        int n, k;
        cin >> n >> k;
        cout << "Case " << kase << ": " << dp[n][k] << endl;
    }
    return 0;
}
