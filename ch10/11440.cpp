// UVa 11440 Help Tomisu
// wangqc
#include<iostream>
#include<cmath>

using namespace std;
// ans = (N!/M!) * phi(M!)
const int maxn = 10000005, M = 100000007;
bool vis[maxn];
int phifac[maxn];     // phifac[n] = phi(n!)

void init()
{
    int m = (int)sqrt(maxn+0.5);
    for(int i = 2; i < m; i++) if(!vis[i])
        for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    phifac[1] = phifac[2] = 1;
    for(int i = 3; i < maxn; i++)
        phifac[i] = (long long)phifac[i-1]*(i-1+vis[i])% M;
}

int main()
{
    init();
    int n, m;
    while(cin >> n >> m && n)
    {
        int ans = phifac[m];
        for(int i = m+1; i <= n; i++)
            ans = (long long) ans * i % M;
        cout << (ans-1+M) % M << endl;      // -1: start counting from 2
    }
    return 0;
}
