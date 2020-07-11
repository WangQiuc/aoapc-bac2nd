// UVa 1643 Angle and Squares
// wangqc
#include<iostream>

using namespace std;

int main()
{
    int n;
    while(cin >> n && n)
    {
        double x1, y1, x2, y2;
        double E = 0, S = 0, e; // |edge| of the square
        cin >> x1 >> y1 >> x2 >> y2;
        double k1 = y1/x1, k2 = y2/x2;
        for(int i = 0; i < n; i++)
            cin >> e, E += e, S += e*e;
        // 2SΔ = cross_product = x1y2 - x2y1 = k2x1x2-k1x1x2 = (k2-k1)x1x2
        // x1 = E(k2+1)/(k2-k1), x2 = E(k1+1)/(k2-k1), 2SΔ = E^2(k1+1)(k2+1)/(k2-k1)
        if(k1 == k2) { printf("0.000\n"); continue; }
        if(k1 > k2) swap(k1, k2);
        printf("%.3lf\n", (E*E*(k1+1)*(k2+1)/(k2-k1) - S) / 2);
    }
    return 0;
}
