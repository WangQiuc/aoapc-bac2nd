// UVa 12230 Crossing Rivers
// wangqc
#include<iostream>

using namespace std;

// waling time: D-ΣL, Each river E(time): AVG(L/v + 3L/v) = 2L/v
// D+Σ(2L/v-L)
int main()
{
    int n, p, l, v, kase = 0;
    double ans;
    while(cin >> n >> ans && (n || ans))
    {
        while(n--)
        {
            cin >> p >> l >> v;
            ans += l * (2.0/v-1);
        }
        printf("Case %d: %.3lf\n\n", ++kase, ans);
    }
    return 0;
}
