// UVa 1625 Color Length
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 5005;
const int INF = 0x3fffffff;

char p[maxn], q[maxn];
int sp[maxn], ep[maxn], sq[maxn], eq[maxn];
int dp[2][maxn], cnt[2][maxn];  // number of chars not finish in p[:i+1] | q[:j+1]


int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> p+1 >> q+1;
        int n = strlen(p+1), m = strlen(q+1);
        for (int i = 0; i < 26; i++)
            sp[i] = INF, ep[i] = 0, sq[i] = INF, eq[i] = 0;
        for (int i = 1; i <= n; i++)
        {
            p[i] -= 'A';
            if (sp[p[i]] == INF) sp[p[i]] = i;
            ep[p[i]] = i;
        }
        for (int i = 1; i <= m; i++)
        {
            q[i] -= 'A';
            if (sq[q[i]] == INF) sq[q[i]] = i;
            eq[q[i]] = i;
        }
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0, t = 0; i <= n; i++, t^=1)
            for (int j = 0; j <= m; j++) if (i || j)
            {
                int vi = i ? dp[t^1][j] + cnt[t^1][j] : INF;
                int vj = j ? dp[t][j-1] + cnt[t][j-1] : INF;
                dp[t][j] = min(vi, vj);
                if (i)
                {
                    cnt[t][j] = cnt[t^1][j];
                    if (i == sp[p[i]] && j < sq[p[i]]) cnt[t][j]++;
                    if (i == ep[p[i]] && j >= eq[p[i]]) cnt[t][j]--;
                }
                else if (j)
                {
                    cnt[t][j] = cnt[t][j-1];
                    if (j == sq[q[j]]) cnt[t][j]++;
                    if (j == eq[q[j]] && !ep[q[j]]) cnt[t][j]--;
                }
            }
        cout << dp[n&1][m] << endl;
    }
    return 0;
}
