// UVa 1228 Integer Transmission
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 64;
int n, d, K[maxn];
unsigned long long dp[maxn+1][maxn+1];
int zcnt = 0, ocnt = 0, Z[maxn], O[maxn]; // Z[i], ith zero from left

bool zero_able(int i, int j)              // can receive 0 only after recevied 1
{
    return i + 1 <= zcnt && (j == ocnt || O[j] + d >= Z[i]);
}

bool one_able(int i, int j)
{
    return j + 1 <= ocnt && (i == zcnt || Z[i] + d >= O[j]);
}

unsigned long long minv, maxv;

void greedy()   // minv - prefer receive 0, maxv - prefer receive 1
{
    minv = maxv = 0;
    int i = 0, j = 0;
    while (i < zcnt || j < ocnt)
    {
        if (zero_able(i, j)) i++, minv <<= 1;
        else j++, minv = minv << 1 | 1;
    }
    i = j = 0;
    while (i < zcnt || j < ocnt)
    {
        if (one_able(i, j)) j++, maxv = maxv << 1 | 1;
        else i++, maxv <<= 1;
    }    
}

void solve()
{
    ocnt = zcnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (K[i]) O[ocnt++] = i;
        else Z[zcnt++] = i;
    }
    greedy();
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i <= zcnt; i++)
        for (int j = 0; j <= ocnt; j++)
        {
            if (zero_able(i, j)) dp[i+1][j] += dp[i][j];
            if (one_able(i, j)) dp[i][j+1] += dp[i][j];
        }
    cout << dp[zcnt][ocnt] << " " << minv << " " << maxv << endl;
}

int main()
{
    int kase = 0;
    unsigned long long k;
    while (cin >> n >> d >> k)
    {
        for (int i = 0; i < n; i++)
            K[n-i-1] = k & 1, k >>= 1;
        cout << "Case " << ++kase << ": ";
        solve();
    }
    return 0;
}
