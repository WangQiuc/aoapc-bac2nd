// UVa 1149 Bin Packing
// wangqc
#include<iostream>
#include <algorithm>

using namespace std;

int a[100005];

int main()
{
    int n, k, T, kase = 0;
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a+n);
        int L = 0, R = n-1, cnt = 0;
        for (; L < R; cnt++)
            if (a[L] + a[R--] <= k) L++;
        if (kase++) cout << endl;
        cout << cnt + (L == R) << endl;
    }
    return 0;
}
