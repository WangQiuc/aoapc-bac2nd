// UVa 1645 Count
// wangqc
#include<cstdio>

const int maxn = 1000, M = 1000000007;
int dp[maxn+5];

void init()
{
    dp[1] = 1;
    for(int i = 2; i <= maxn; i++)
        for(int j = 1; j < i; j++) if((i-1)%j == 0)
            (dp[i] += dp[j]) %= M;
}

int main()
{
    init();
    int n, kase = 0;
    while(scanf("%d", &n) == 1)
        printf("Case %d: %d\n", ++kase, dp[n]);
    return 0;
}
