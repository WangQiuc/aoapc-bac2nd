// UVa 10622 Perfect P-th Powers
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;
typedef long long ll;

const int maxn = 50000;
int cp;
ll prime[maxn];
bool vis[maxn];

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

void init()
{
    int m = sqrt(maxn+0.5);
    cp = 0;
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        prime[cp++] = i;
        if(i <= m) for(int j = i*i; j < maxn; j += i) vis[i] = true;
    }
}

int decompose(ll &x, ll p)      // fundamental theorem: decompose x from p^cnt
{
    int cnt = 0;
    while(x % p == 0)
        x /= p, cnt++;
    return cnt;
}

int main()
{
    init();
    ll n;
    while(cin >> n && n)
    {
        ll x = n < 0 ? -n : n, ans = 0;
        for(int i = 0; ans != 1 && i < cp && prime[i] <= x; i++) 
            if(x % prime[i] == 0) ans = gcd(ans, decompose(x, prime[i]));
        if (x > 1 || !ans) ans = 1;     // ans = 0 when n = {-1, 1}
        if (n < 0) ans /= (ans & -ans); // max odd factor
        cout << ans << endl;
    }
    return 0;
}
