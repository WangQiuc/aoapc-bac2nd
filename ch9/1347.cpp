// UVa 1347 Tour
// wangqc
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn = 55;
double x[maxn], y[maxn], dist[maxn][maxn], dp[maxn][maxn];

int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &x[i], &y[i]);
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                dist[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
        for (int j = 0; j < n-2; j++) 
            dp[n-2][j] = dist[n-1][n-2] + dist[n-1][j];
        for (int i = n-3; i > 0; i--)
            for (int j = 0; j < i; j++)
                dp[i][j] = min(dist[i+1][i]+dp[i+1][j], dist[i+1][j]+dp[i+1][i]);
        printf("%.2lf\n", dist[1][0] + dp[1][0]);
    }
    return 0;
}
