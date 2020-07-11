// UVa 1210 Sum of Consecutive Prime Numbers
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

const int maxn = 10005;
int d[maxn], primes[maxn];
bool vis[maxn];

void init()
{
    int n = 0, m = sqrt(maxn+0.5);
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        primes[n++] = i;
        if(i <= m) for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    }
    for(int i = 0; i < n; i++)
        for(int j = i, s = 0; j < n && s + primes[j] < maxn; j++)
            d[s += primes[j]]++;
}

int main()
{
    init();
    int n;
    while(cin >> n && n)
        cout << d[n] << endl;
    return 0;
}
