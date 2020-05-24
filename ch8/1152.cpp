// UVa 1152  Values whose Sum is 0
// wangqc
#include<cstdio>
#include<algorithm>

using namespace std;

const int maxn = 4000 + 5;
int A[maxn], B[maxn], C[maxn], D[maxn], sum[maxn*maxn];

int main()
{
    int n, c, T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
        c = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                sum[c++] = A[i] + B[j];
        sort(sum, sum+c);
        long long cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cnt += upper_bound(sum, sum+c, -C[i]-D[j]) - lower_bound(sum, sum+c, -C[i]-D[j]);
        printf("%lld\n", cnt);
        if (T) printf("\n");
    }
    return 0;
}
