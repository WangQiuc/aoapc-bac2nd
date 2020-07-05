// UVa 1393 Highways
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 300;
int g[maxn+1][maxn+1];

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int main()
{
    for(int i = 1; i <= maxn; i++)
        for(int j = 1; j <= maxn; j++)
            g[i][j] = gcd(i, j);
    int n, m;
    while(cin >> n >> m && n)
    {   // count number of '\' then times 2 by counting number of a*b squares
        int cnt = 0;
        for(int a = 1; a <= m; a++)
            for(int b = 1; b <= n; b++) if(g[a][b] == 1)
                cnt += (m-a)*(n-b) - (max(0, m-(a<<1))*max(0, n-(b<<1)));
        cout << (cnt<<1) << endl;
    }
    return 0;
}
