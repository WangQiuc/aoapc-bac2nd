// UVa 1649 Binomial coefficients
// wangqc
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
typedef long long ll;

vector<pair<ll, ll> > q;
ll m;
ll C(ll n, ll k)
{
    ll x = 1;
    for(int i = 1; i <= k; i++)
    {
        if(x/i > m/(n-i+1)) return m+1;
        x = x*(n-i+1)/i;    // not use "*="" to avoid float division
    }
    return x;
}

void binary_search()
{
    for(int k = 1; C(k<<1, k) <= m; k++)
    {
        ll lo = (k<<1) - 1, hi = m+1;
        while(lo <= hi)
        {
            ll mid = (lo + hi) >> 1;
            ll x = C(mid, k);
            if (x < m) lo = mid+1;
            else if (x > m) hi = mid-1;
            else
            {
                q.push_back(make_pair(mid, k));
                if (mid != k<<1) q.push_back(make_pair(mid, mid-k));
                break;
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        q.clear();
        cin >> m;
        binary_search();
        sort(q.begin(), q.end());
        printf("%zu\n(%lld,%lld)", q.size(), q[0].first, q[0].second);
        for(int i = 1; i < q.size(); i++)
            printf(" (%lld,%lld)", q[i].first, q[i].second);
        cout << endl;
    }
    return 0;
}
