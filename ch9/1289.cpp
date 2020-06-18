// UVa 1289 Stacking Plates
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 55, maxm = 2505;
const int INF = 0x3f3f3f3f;
int p, n, m, cnt[maxm], a[maxm], f[maxm][maxn];
bool v[maxm][maxn];     // v[i][j] block i from j pile

void init()
{
    p = m = 0;
    for (int i = 1; i <= n; i++)
    {
        int h; cin >> h;
        for (int j = 1; j <= h; j++)
            cin >> a[++p], a[p] = 100*a[p] + i;
    }
    memset(cnt, 0, sizeof(cnt));
    memset(v, 0, sizeof(v));
    memset(f, INF, sizeof(f));
    sort(a+1, a+p+1);
    p = unique(a+1, a+p+1) - (a+1);
    for (int i = 1; i <= p; i++)
    {
        int j = i;
        v[++m][a[j]%100] = 1;
        while (a[j]/100 == a[j+1]/100 && j < p)
            v[m][a[++j]%100] = true;
        cnt[m] = j-i+1, i = j;
    }
}

// suppose each n pile has unique color, final pile has x color blocks, then 
// total number is (x-n) splits + (x-1) join = 2x-n-1
// f[i][j] is total color blocks # x when ith block from pile j
int solve()
{
    for (int j = 1; j <= n; j++)
        if (v[1][j]) f[1][j] = cnt[1];
    for (int i = 2; i <= m; i++)
        for (int j = 1; j <= n; j++) if (v[i][j])
            for (int k = 1; k <= n; k++)
                // reduce one block if i-1 and i are from same pile   
                f[i][j] = min(f[i][j], f[i-1][k]+cnt[i]-(v[i][k]&&(k!=j||cnt[i]==1)));
    int x = INF;
    for (int j = 1; j <= n; j++)
        x = min(x, f[m][j]);
    return x * 2 - n - 1;
}

int main()
{
    int kase = 0;
    while (cin >> n)
    {
        init();
        cout << "Case " << ++kase << ": " << solve() << endl;
    }
    return 0;
}
