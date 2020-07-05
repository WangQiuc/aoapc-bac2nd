// UVa 1639 Candy
// wangqc
#include<iostream>
#include<cmath>

using namespace std;
typedef long double LD;
const int maxn = 200005;
LD lnF[maxn*2+1];  // lnF[x] = ln(x!)
// C(n, m) = n!/(m!(n-m)!)
inline LD lnC(int n, int m) {  return lnF[n] - lnF[m] - lnF[n-m]; }

// last open box 1, i candies in box 2: C(2n-i,n)*p^(n+1)*(1-p)^(n-i)
// last open box 2, i candies in box 1: C(2n-i,n)*p^(n-i)*(1-p)^(n+1)
// Σ(i*(e^v1i + e^v2i)), v1i = ln(C(2n-i,i)) + (n+1)*lnp + (n-i)*ln(1-p)
int main()
{
    lnF[0] = 0;
    for(int i = 1; i <= maxn; i++)
        lnF[i] = lnF[i-1] + log(i);
    int n, kase = 0;
    double p;
    while(cin >> n >> p)
    {
        double ans = 0;
        for(int i = 0; i <= n; i++)
        {
            LD c = lnC(2*n-i, n);
            LD v1 = c + (n+1)*log(p) + (n-i)*log(1-p);
            LD v2 = c + (n-i)*log(p) + (n+1)*log(1-p);
            ans += i*(exp(v1)+exp(v2));
        }
        printf("Case %d: %.6lf\n", ++kase, ans);
    }
    return 0;
}
