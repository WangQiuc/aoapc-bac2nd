// UVa 12105 Bigger is Better
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 105, maxm = 3005;
// matches # for digit 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
const int match[] = {6, 2, 5, 5, 4, 5, 6, 3, 7 ,6};
// dp[i][j]: max value x's length built with i matches and x % m = j
// v[i][j]: max value for state(i, j)
int n, m, dp[maxn][maxm], v[maxn][maxm];

int main()
{
    int kase = 0;
    while (cin >> n >> m && n)
    {
        cout << "Case " << ++kase << ": ";
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                int &ans = dp[i][j];
                ans = v[i][j] = -1;
                if (j == 0) ans = 0;
                for (int d = 9; d >= 0; d--) if (i >= match[d])
                {
                    int x = dp[i-match[d]][(j*10+d)%m] + 1;
                    if (x > max(0, ans)) ans = x, v[i][j] = d;
                }
            }
        if (v[n][0] >= 0)
        {
            int i = n, j = 0;
            for (int d = v[i][j]; d >= 0; d = v[i][j])
            {
                cout << d;
                i -= match[d], j = (j*10+d)%m;
            }
            cout << endl;
        }
        else cout << -1 << endl;
    }
    return 0;
}
