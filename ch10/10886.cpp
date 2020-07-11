// UVa 10886 Standard Deviation
// wangqc
#include<iostream>
#include<cmath>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

ull seed;
long double gen()
{
    static const ld Z = (ld)1.0 / (1ll << 32);
    seed >>= 16;
    seed &= (1ull << 32) - 1;
    seed *= seed;
    return seed * Z;
}

// m = (1/n)Σxi, std = (1/n)Σ(xi-m)^2 = (1/n)Σxi^2 - m^2
int main()
{
    int T, kase = 0;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n >> seed;
        double s1 = 0, s2 = 0;
        for(int i = 0; i < n; i++)
        {
            double x = gen();
            s1 += x*x, s2 += x;
        }
        s1 /= n, s2 /= n;
        printf("Case #%d: %.5lf\n", ++kase, sqrt(s1-s2*s2));
    }
    return 0;
}
