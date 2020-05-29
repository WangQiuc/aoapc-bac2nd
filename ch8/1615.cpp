// UVa 1615 Highway
// wangqc
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn = 100005;
int n, L, D;
struct itvl     // interval
{
    double s, e;
    itvl() {}
    itvl(double s, double e): s(s > 0 ? s : 0), e(e < L ? e : L) {}
    bool operator < (const itvl &rhs) const {
        return e < rhs.e || (e == rhs.e && s > rhs.s);
    }
} itvls[maxn];

int main()
{
    while (cin >> L)
    {
        cin >> D >> n;
        D *= D;
        double x, y, r, curr = -1;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            r = sqrt(D - y*y);
            itvls[i] = itvl(x-r, x+r);
        }
        sort(itvls, itvls+n);
        for (int i = 0; i < n; i++) if (itvls[i].s > curr) 
            curr = itvls[i].e, cnt++;
        cout << cnt << endl;
    }
    return 0;
}
