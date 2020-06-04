// UVa 1025 A Spy in the Metro
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 55;
const int maxt = 205;
const int INF = 0x3fffffff;

int t[maxn], dp[maxt][maxn];
bool has_train[maxt][maxn][2];

int main()
{
    int n, T, kase = 0;
    while (cin >> n >> T && n)
    {
        int M1, M2, d;
        for (int i = 1; i < n; i++) cin >> t[i];
        memset(has_train, 0, sizeof(has_train));
        cin >> M1;
        while (M1--)
        {
            cin >> d;
            for (int j = 1 ; j < n; j++)
            {
                if (d <= T) has_train[d][j][0] = true;
                d += t[j];
            }
        }
        cin >> M2;
        while (M2--)
        {
            cin >> d;
            for (int j = n-1 ; j > 0; j--)
            {
                if (d <= T) has_train[d][j+1][1] = true;
                d += t[j];
            }
        }
        for(int i = 1; i < n; i++) dp[T][i] = INF;
        dp[T][n] = 0;
        for (int i = T-1; i >= 0; i--)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i+1][j] + 1;  // wait at station j
                if (j < n && has_train[i][j][0] && i+t[j] <= T)
                    dp[i][j] = min(dp[i][j], dp[i+t[j]][j+1]);    // travel righthand
                if (j > 1 && has_train[i][j][1] && i+t[j-1] <= T)
                    dp[i][j] = min(dp[i][j], dp[i+t[j-1]][j-1]);  // travel lefthand
            }
        cout << "Case Number " << ++kase << ": ";
        if (dp[0][1] >= INF) cout << "impossible\n";
        else cout << dp[0][1] << endl;
    }
    return 0;
}
