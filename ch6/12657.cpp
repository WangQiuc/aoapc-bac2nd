// UVa12657 Boxes in a Line
// wangqc

#include <cstdio>
#include <algorithm>
typedef long long LL;

using namespace std;

const int maxn = 100005;
int n, left[maxn], right[maxn];

inline void link(int L, int R)
{
    left[R] = L, right[L] = R;
}

int main()
{
    int m, kase = 0;
    while (scanf("%d%d", &n, &m) == 2)
    {
        for (int i = 1; i < n; i++)
            left[i] = i-1, right[i] = i+1;
        left[0] = n, left[n] = n-1; right[0] = 1, right[n] = 0;
        int op, X, Y, rev = 0;
        while(m--)
        {
            scanf("%d", &op);
            if (op == 4) rev ^= 1;
            else
            {
                scanf("%d%d", &X, &Y);
                if (op == 3 && right[Y] == X) swap(X, Y);
                if (op != 3 && rev) op = 3 - op;
                if (op == 1 && X == left[Y]) continue;
                if (op == 2 && X == right[Y]) continue;
                int LX = left[X], RX = right[X], LY = left[Y], RY = right[Y];
                if (op == 1) { link(LX, RX); link(LY, X); link(X, Y); }
                if (op == 2) { link(LX, RX); link(Y, X); link(X, RY); }
                if (op == 3)
                {
                    if (right[X] == Y) { link(LX, Y); link(Y, X); link(X, RY); }
                    else { link(LX, Y); link(Y, RX); link(LY, X); link(X, RY); }
                }
            }     
        }
        int b = 0;
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            b = right[b];
            if (i & 1) ans += b;
        }
        if (rev && !(n&1)) ans = (LL)n*(n+1)/2 - ans;
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}
