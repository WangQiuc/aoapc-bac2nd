// UVa 10366 Faucet Flow
// wangqc
#include<iostream>

using namespace std;

const int maxn = 1005;
int L, R, lmax, rmax, li, ri, lh[maxn], rh[maxn];

int solve()
{
    if (lmax > rmax) swap(lmax, rmax), swap(li, ri), swap(lh, rh), swap(L, R);
    int lt = 0, rt = 0;
    for (int i = L, h = lh[L]; i > li; i--)
        lt += h, h = max(h, lh[i-1]);
    if (lmax == rmax)
    {
        for (int i = R, h = rh[R]; i > ri; i--)
            rt += h, h = max(h, rh[i-1]);
        return ((li + ri + 1) * lmax + min(lt, rt) * 2) * 2;  
    }
    for (ri = 0; ri < R && rh[ri] < lmax; ri++);
    for (int i = ri, h = lmax; rh[i] <= lmax; i++)
        rt += h, h = max(h, rh[i+1]);
    return ((li + ri + 1) * lmax + (lt > rt ? lt + rt : 2 * lt)) * 2;
}

int main()
{
    while (cin >> L >> R && L)
    {
        lmax = rmax = 0;
        L = -L / 2, R = R / 2;
        for (int i = L; i >= 0; i--)
        {
            cin >> lh[i];
            if (lh[i] >= lmax) lmax = lh[i], li = i;
        }
        for (int i = 0; i <= R; i++)
        {
            cin >> rh[i];
            if (rh[i] > rmax) rmax = rh[i], ri = i;
        }
        cout << solve() << endl;
    }
    return 0;
}
