// UVa 11346 Probability
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

const double eps = 1e-6;
// P = 1 - (s+s∫[s/b,s](1/x) / (a*b)
int main()
{
    int T;
    cin >> T;
    while(T--) 
    {
        double a, b, s, ans;
        cin >> a >> b >> s;
        double m = a*b;
        if(fabs(s) < eps) ans = 1;
        else if (s > m) ans = 0;
        else ans = 1 - (1+log(m/s))*s/m;
        printf("%.6lf%%\n", ans*100);
        
    }
    return 0;
}
