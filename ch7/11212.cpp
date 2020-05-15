// UVa 11212 Editing a Book
// wangqc
#include<cstdio>
#include<cstring>

using namespace std;

const int maxn = 9;
int n, a[maxn];

bool is_target()
{
    for (int i = 0; i < n; i++)
        if (a[i] != i+1) return false;
    return true;
}

int h()
{
    int cnt = a[0] != 1;
    for (int i = 1; i < n-1; i++)
        if (a[i]+1 != a[i+1]) cnt++;
    return cnt;
}

bool dfs(int d, int maxd)
{
    if ((maxd-d)*3 < h()) return false;   // each round correct 3 slots at most 
    if (is_target()) return true;
    int b[maxn], pa[maxn];
    memcpy(pa, a, sizeof(a));
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            int cnt = 0;
            for (int k = 0; k < n; k++)
                if (k < i || k > j) b[cnt++] = a[k];
            for (int k = 0; k < cnt; k++)
            {
                int cnt2 = 0;
                for (int p = 0; p < k; p++) a[cnt2++] = b[p];
                for (int p = i; p <= j; p++) a[cnt2++] = pa[p];
                for (int p = k; p < cnt; p++) a[cnt2++] = b[p];
                if (dfs(d+1, maxd)) return true;
                memcpy(a, pa, sizeof(a));
            }
        }
    return false;
}

int solve()
{
    if (is_target()) return 0;
    int maxs = 8;
    for (int maxd = 1; maxd <= maxs; maxd++)
        if (dfs(0, maxd)) return maxd;
    return maxs;
}

int main()
{
    int kase = 0;
    while (scanf("%d", &n) == 1 && n)
    {
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        printf("Case %d: %d\n", ++kase, solve());
    }
    return 0;
}
