// UVa 1642 Magical GCD
// wangqc
#include<iostream>
#include<map>

using namespace std;
typedef long long ll;
const int maxn = 100005;
int n;
ll a[maxn];

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        map<ll, int> idx;
        ll ans = 0;
        for(int i = 0; i < n; i++)
        {
            map<ll, int> idx2;
            idx[0] = i;
            for(auto p : idx)
            {
                ll g = gcd(p.first, a[i]);
                if(!idx2.count(g) || idx2[g] > p.second) idx2[g] = p.second;
            }
            for(auto p : idx2)
                ans = max(ans, p.first*(i+1-p.second));
            idx = idx2;
        }
        cout << ans << endl;
    }
    return 0;
}