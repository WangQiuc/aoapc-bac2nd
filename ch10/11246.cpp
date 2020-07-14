// UVa 11246 K-Multiple Free set
// wangqc
#include<iostream>

using namespace std;
typedef long long ll;

// n - n/k + n/k^2 - n/k^3 ... Σ(-1)^i * n/k^i
int main()
{
    int T;
    ll n, k, x, ans;
    cin >> T;
    while(T--)
    {
        cin >> n >> k;
        ans = x = n;
        while(x) ans += (x = -x/k);
        cout << ans << endl;
    }
    return 0;
}
