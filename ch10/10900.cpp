// UVa 10900 So you want to be a 2n-aire?
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 35;
double d[maxn];

int main()
{
    int n;
    double t;
    while(cin >> n >> t && n)
    {
        d[n] = 1<<n;
        for(int i = n-1; i >= 0; i--)
        {
            double p0 = max(t, double(1<<i) / d[i+1]);
            double p = (p0-t) / (1-t);
            d[i] = (double)(1<<i)*p + (1+p0)/2 * d[i+1] * (1-p);
        }
        printf("%.3lf\n", d[0]);
    }
    return 0;
}
