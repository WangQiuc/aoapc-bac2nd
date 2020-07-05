// UVa 11971 Polygon
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

// fraction reduction
void reduce(ll &a, ll &b)
{
    ll g = gcd(a, b);
    a /= g, b /= g;
}

// the length of longest segment < 1/2 entire length
// p = 1 -(k+1)/(2^k) - all k points falls in (1/2) one half (k+1 possible halves)
int main()
{
    int T, n, k;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> n >> k;
        ll b = 1ll << k;
        ll a = b - k - 1;
        reduce(a, b);
        printf("Case #%d: %lld/%lld\n", kase, a, b);
    }
    return 0;
}
