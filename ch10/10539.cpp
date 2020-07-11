// UVa 10539 Almost Prime Numbers
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;
typedef long long ll;

const int maxn = 1000005;
vector<int> primes;
bool vis[maxn];
void init()
{
    int m = sqrt(maxn+0.5);
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        primes.push_back(i);
        if(i <= m) for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    }
}

ll f(ll n)
{
    ll cnt = 0;
    for(int p : primes)
    {
        ll x = (ll)p * p;
        if (x > n) break;
        while(x <= n)
            cnt++, x *= p;
    }
    return cnt;
}

int main()
{
    init();
    int T;
    cin >> T;
    while(T--)
    {
        ll lo, hi;
        cin >> lo >> hi;
        cout << f(hi) - f(lo-1) << endl;
    }
    return 0;
}
