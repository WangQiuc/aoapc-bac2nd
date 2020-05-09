// UVa1594 Ducci Sequence
// wangqc

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000;

int transform(vector<int> &ds)
{
    int tot = 0, n = ds.size(), first = ds[0];
    for (int i = 0; i < n - 1; i++)
        tot += (ds[i] = abs(ds[i] - ds[i+1]));
    return tot + (ds[n-1] = abs(ds[n-1] - first));
}

int main()
{
    int T, n, x, i;
    cin >> T;
    while (T--)
    {
        cin >> n;
        vector<int> ds;
        while (n--)
        {
            cin >> x;
            ds.push_back(x);
        }
        for(i = 0; i < maxn && transform(ds); i++);
        (i == maxn) ? printf("LOOP\n") : printf("ZERO\n");
    }
    return 0;
}
