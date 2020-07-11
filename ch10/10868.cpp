// UVa 10868 Bungee Jumping
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

const double g = 9.81;
// E = 1/2kΔl^2, G = mgh, M = 1/2mv^2
// Stuck in air, E = G, h = l+Δl < s
// Otherwise, G = M+E (E=0 if l >= s), h=s, mgs = M+1/2k(max(0,s-l)^2)
int main()
{
    double k, l, s, m;
    while(cin >> k >> l >> s >> m && k+l+s+m)
    {
        double maxh = l + (m*g+sqrt(m*m*g*g+2.0*k*l*m*g)) / k;
        if(s > maxh) cout << "Stuck in the air.\n";
        else
        {
            double v2 = 2.0*g*s;
            if(s > l) v2 -= k*(s-l)*(s-l)/m;
            if (v2 <= 100) cout << "James Bond survives.\n";
            else cout << "Killed by the impact.\n";
        }
    }
    return 0;
}
