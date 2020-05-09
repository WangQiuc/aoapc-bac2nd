// UVa815 Flooded
// wangqc

#include <iostream>
#include <algorithm>

using namespace std;

int elevations[1000];

int main()
{
    int m, n, sz, i, kase = 0;
    double flood;
    while (cin >> m >> n, m && n)
    {
        sz = m * n;
        for (i = 0; i < sz; i++)
            cin >> elevations[i];
        elevations[i] = 1 << 30;
        cin >> flood;
        flood /= 100.0;
        sort(elevations, elevations + sz);
        for (i = 1; i <= sz; i++)
            if ((flood += elevations[i-1]) / i <= elevations[i]) break;
        printf("Region %d\nWater level is %.2lf meters.\n", ++kase, flood / i);
        printf("%.2lf percent of the region is under water.\n\n", (double) i * 100.0 / sz);
    }
    return 0;
}
