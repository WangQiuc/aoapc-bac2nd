// UVa 116 Unidirectional TSP
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 105;
const int INF = 0x3fffffff;
int m, n, a[maxn][maxn], dp[maxn][maxn], path[maxn][maxn];

int main()
{
    while (cin >> m >> n && m)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        int ans = INF, first = 0;
        for (int j = n-1; j >= 0; j--)
            for (int i = 0; i < m; i++)
            {
                if (j == n-1) dp[i][j] = a[i][j];
                else
                {
                    int rows[3] = {(i-1+m)%m, i, (i+1)%m};
                    sort(rows, rows+3);     // lexicographical order
                    dp[i][j] = INF;
                    for (int d = 0; d < 3; d++)
                    {
                        int v = dp[rows[d]][j+1] + a[i][j];
                        if (v < dp[i][j]) dp[i][j] = v, path[i][j] = rows[d];

                    }
                }
                if (j == 0 && dp[i][j] < ans) {ans = dp[i][j], first = i;}
            }
        cout << first + 1;
        for (int i = path[first][0], j = 1; j < n; i = path[i][j], j++)
            cout << " " << i + 1;
        cout << endl << ans << endl;
    }
    return 0;
}
