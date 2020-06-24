// UVa 1543 Telescope
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn = 45;
const double pi2 = acos(-1)*2;
int n, m;
// dp[v][i][j], select v vertices from pi to pj; sz[a][b][c] size of triangle abc 
double dp[maxn][maxn][maxn], sz[maxn][maxn][maxn];

struct Point { double x, y; } pt[maxn];
double dist(Point a, Point b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double area(Point a, Point b, Point c)
{
    double x = dist(a, b), y = dist(b, c), z = dist(a, c);
    double p = (x+y+z) / 2;
    return sqrt(p*(p-x)*(p-y)*(p-z));
}

void init()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            for (int k = j+1; k <= n; k++)
                sz[i][j][k] = area(pt[i], pt[j], pt[k]);
}

int main()
{
    while (cin >> n >> m && n)
    {
        double p, ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> p;
            pt[i].x = cos(p*pi2), pt[i].y = sin(p*pi2);
        }
        init();
        for (int v = 3; v <= m; v++)
            for (int i = 1; i < n; i++)
                for (int j = i+2; j <= n; j++)
                    for (int k = i+1; k < j; k++)
                        dp[v][i][j] = max(dp[v][i][j], dp[v-1][i][k]+sz[i][k][j]);
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                ans = max(ans, dp[m][i][j]);
        printf("%.6lf\n", ans);
    }
    return 0;
}
