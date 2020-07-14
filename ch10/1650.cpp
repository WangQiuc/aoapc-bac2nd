// UVa 1650 Number String
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

const int maxn = 1005;
const ll M = 1e9+7;
// dp[i][j]: s[i] place j (prefix sum)
ll dp[maxn][maxn];
char s[maxn];

void add_mod(ll &x, ll y) { x = (x + y + M) % M; }

int main()
{
    while(cin >> s+1)
    {
        int n = strlen(s+1);
        dp[0][1] = 1;
        for(int i = 1; i <= n; i++)         // 0-index
            for(int j = 1; j <= i+1; j++)   // 1-index
            {
                dp[i][j] = dp[i][j-1];
                if(s[i] != 'D') add_mod(dp[i][j], dp[i-1][j-1]);  // sum(0,j-1)
                if(s[i] != 'I')  add_mod(dp[i][j], dp[i-1][i] - dp[i-1][j-1]);    // sum(j, i)
            }
        cout << dp[n][n+1] << endl;
    }
    return 0;
}
