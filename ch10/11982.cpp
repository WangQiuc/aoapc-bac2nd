// UVa 11982 Fantasy Cricket
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

const ll M = 1e9+7;
const int maxn = 1001;
ll dp[maxn][maxn];
char s[maxn];

// dp[i][j] plan # that s[:i] has j 'U' not allocated, 'D' is always allocated as it must be allocated before s[i]
// s[i] = 'U', s[i] go backward, dp[i-1][j-1]*1 + dp[i-1][j]*j
// (j-1 'U' not allocated before s[i] and s[i] not refilled, so total j 'U' not allocated
// or j 'U' not allocated before s[i] and s[i] be refilled by any unallocated 'U' before so still j 'U' not allocated)
// s[i] = 'D', s[i] go upward, dp[i-1][j]*j + dp[i-1][j+1]*(j+1)*(j+1)
// (j 'U' not allocated before s[i] and s[i] go to any 'U' slot before, s[i] not filled so still j 'U' not allocated
// or j+1 'U' not allocated before s[i] and s[i] go to any 'U' slot before, s[i] filled by any j+1 'U' so total j 'U' not allocated)
int main()
{
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> s+1;
        int n = strlen(s+1);
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++)
        {
            if(s[i] == 'U') for(int j = 0; j <= i; j++)
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] + dp[i-1][j]*j % M) % M;
            else if (s[i] == 'D') for(int j = 0; j <= i; j++)
                dp[i][j] = (dp[i][j] + dp[i-1][j]*j % M + dp[i-1][j+1]*(j+1)%M*(j+1)%M) % M;
            else for(int j = 0; j <= i; j++)
                dp[i][j] = dp[i-1][j];
        }
        cout << "Case " << kase << ": " << dp[n][0] << endl; 
    }
    return 0;
}
