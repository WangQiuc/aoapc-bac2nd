// UVa 11526 H(n)
// wangqc
#include<iostream>
#include<cmath>

using namespace std;
typedef long long ll;

// two ends, left end n/idx = val, right end n/val = idx_range(n/(val+1), n/val]
int main()
{
    int n, T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        int m = sqrt(n+0.5);
        ll s = 0;
        for(int i = 1; i <= m; i++)
        {
            int x = n / i;          // left end and right end range's hi
            int cnt = x - n/(i+1);  // right end range's lo
            s += (ll)cnt*i + (i == x ? 0 : x);   // exclude duplicated middle point
        }
        cout << s << endl;
    }
    return 0;
}
