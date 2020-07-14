// UVa 11186 Circum Triangle
// wangqc
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;
const double pi = acos(-1);
double a[505];

// enumerate two points (i,j), the contribution a (i,j) make is: (n+2i-2j)*S(ioj):
// when ioj < 180: 3rd point k is not in [i,j] (n-(j-i+1)), S += S(ioj); else (j-i-1) S -= S(ioj)
// when ioj > 180: negative sin will negate it back correctly
int main()
{
    int n;
    double r;
    while(cin >> n >> r && n)
    {
        for(int i = 0; i < n; i++)
            cin >> a[i], a[i] *= pi/180;
        sort(a, a+n);
        double s = 0;
        for(int i = 0; i < n-1; i++)
            for(int j = i+1; j < n; j++)
                s += (n+(i<<1)-(j<<1))*sin(a[j]-a[i]);    // S(ioj) = r*r*sin(a0b) / 2
        cout << (long long)floor(s*r*r/2+0.5) << endl;
    }
    return 0;
}
