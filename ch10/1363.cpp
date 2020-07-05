// UVa 1363 Joseph's Problem
// wangqc
#include<iostream>

using namespace std;
typedef long long ll;
// arithmetic sequence sum, a0 = a, an = a-nd
inline ll sum(int a, int d, int n) { return (ll)(a+a-n*d)*(n+1)/2; }

int main()
{
    int n, k;
    while(cin >> n >> k)
    {
		int i = 1;
		ll ans = 0;
		while(i <= n)
		{
			int q = k % i, p = k / i;
			int cnt = n - i;
			if(p > 0 && cnt > q/p) cnt = q/p;
			ans += sum(q, p, cnt);
			i += cnt + 1;
		}
		cout << ans << endl;
    }
    return 0;
}
