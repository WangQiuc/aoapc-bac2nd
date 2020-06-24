// UVa 1379 Pitcher Rotation
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

struct Pitcher
{
    int id, rate;
    Pitcher(int id=0, int rate=0): id(id), rate(rate) {}
    bool operator < (const Pitcher &rhs) const { return rate > rhs.rate; }
} p[105][105];

int n, m, g, s[220], dp[2][6][6][6][6];

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m >> g, g += 10;
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
                cin >> p[i][j].rate, p[i][j].id = j;
            sort(p[i]+1, p[i]+n+1);
        }
        for (int i = 1; i <= g; i++)
            cin >> s[i];
        memset(dp, 0, sizeof(dp));
        int t = 0;
        for (int i = 1; i <= g; i++)
        {
            t ^= 1;
            memset(dp[t], 0, sizeof(dp[t]));
            for (int x1 = 0; x1 <= 5; x1++)
                for (int x2 = 0; x2 <= 5; x2++)
                    for (int x3 = 0; x3 <= 5; x3++)
                        for (int x4 = 0; x4 <= 5; x4++)
                        {
                            if(s[i]) for (int x=1; x<=5; x++)
                            {
                                int id = p[s[i]][x].id, rate = p[s[i]][x].rate;
                                if (i>1 && id==p[s[i-1]][x1].id) continue;
                                if (i>2 && id==p[s[i-2]][x2].id) continue;
                                if (i>3 && id==p[s[i-3]][x3].id) continue;
                                if (i>4 && id==p[s[i-4]][x4].id) continue;
                                dp[t][x][x1][x2][x3] = max(dp[t][x][x1][x2][x3], dp[t^1][x1][x2][x3][x4]+rate);
                            }
                            else dp[t][0][x1][x2][x3] = max(dp[t][0][x1][x2][x3], dp[t^1][x1][x2][x3][x4]);
                        }
        }
        int ans = 0;
            for (int x1 = 0; x1 <= 5; x1++)
                for (int x2 = 0; x2 <= 5; x2++)
                    for (int x3 = 0; x3 <= 5; x3++)
                        for (int x4 = 0; x4 <= 5; x4++)
                            ans = max(ans, dp[t][x1][x2][x3][x4]);                  
        printf("%.2lf\n", ans/100.0);
    }
    return 0;
}
