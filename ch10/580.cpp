// UVa 580 Critical Mass
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

int f[31], g[31];

int main()
{
    for(int i = 0; i <= 2; i++)
        f[i] = 0, g[i] = 1<<i;
    for(int n = 3; n <= 30; n++)
    {
        f[n] = 1<<(n-3);
        for(int i = 2; i <= n-2; i++)
            f[n] += g[i-2] * (1<<(n-i-2));
        g[n] = (1<<n) - f[n];
    }
    int n;
    while(cin >> n && n)
        cout << f[n] << endl;
    return 0;
}
