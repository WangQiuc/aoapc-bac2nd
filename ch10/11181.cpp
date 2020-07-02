// UVa 11181 Probability|Given
// wangqc
#include<cstdio>
#include<cstring>

using namespace std;

const int maxn = 25;
int n, r, a[maxn];
double P[maxn], sum[maxn];

void dfs(int i, int cnt, double p)
{
    if (cnt > r || i-cnt > n-r) return;
    if (i == n)
    {
        sum[n] += p;
        printf("de %lf\n", p);
        for(int i = 0; i < n; i++) if(a[i])
            sum[i] += p;
        return;
    }
    a[i] = 0;
    dfs(i+1, cnt, p*(1-P[i]));
    a[i] = 1;
    dfs(i+1, cnt+1, p*P[i]);
}

int main()
{
    int kase = 0;
    while(scanf("%d%d", &n, &r) == 2 && n)
    {
        for(int i = 0; i < n; i++)
            scanf("%lf", &P[i]);
        memset(sum, 0, sizeof(sum));
        dfs(0, 0, 1.0);
        printf("Case %d:\n", ++kase);
        for(int i = 0; i < n; i++)
            printf("%.6lf\n", sum[i]/sum[n]);
    }
    return 0;
}
