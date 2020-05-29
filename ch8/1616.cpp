// UVa 1616 Caravan Robbers
// wangqc
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long double LD;
const int maxn = 100005;
const LD eps = 1e-11;
int n;
struct itvl     // interval
{
    int s, e;
    bool operator < (const itvl &rhs) const {
        return s < rhs.s || (s == rhs.s && e < rhs.e);
    }
} itvls[maxn];

bool valid(LD x)
{
    LD cur = 0;
    for (int i = 0; i < n; i++)
    {
        cur = max(cur, (LD)itvls[i].s);
        cur += x;
        if (cur - itvls[i].e > eps) return false;
    }
    return true;
}

int main()
{
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
            cin >> itvls[i].s >> itvls[i].e;
        sort(itvls, itvls + n);
        LD L, R, M;
        for (L = 0, R = itvls[n-1].e; R - L > eps; valid(M) ? L = M : R = M)
            M = (L + R) / 2;
        int p, q;
        for (q = 1; q <= n+1; q++)
        {
            p = round(L * q);
            if (fabs((LD)p / q - L) < eps) break;
        }
        cout << p << "/" << q << endl;
    }
    return 0;
}
