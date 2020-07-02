// UVa 12034 Race
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1000, M = 10056;
int C[maxn+1][maxn+1], f[maxn+1];

void init()
{
    for(int i = 0; i <= maxn; i++)
    {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % M;
    }
    f[0] = 1;
    for(int n = 1; n <= maxn; n++)
    {   // f(n) = ΣC(n,i)*f(n-i), i players rank 1st among n players
        f[n] = 0;
        for(int i = 1; i <= n; i++)
            f[n] = (f[n] + C[n][i] * f[n-i]) % M;
    }
}

int main()
{
    init();
    int n, T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> n;
        cout << "Case " << kase << ": " << f[n] << endl;
    }
    return 0;
}
