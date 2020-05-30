// UVa 1617 Laptop
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 100005;

struct seg     // segment
{
    int l, r;
    bool operator < (const seg &rhs) const {
        return l < rhs.l || (l == rhs.l && r < rhs.r);
    }
} segs[maxn];

int main()
{
    int n, T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> segs[i].l >> segs[i].r;
        sort(segs, segs+n);
        int cnt = 0, L = -1, R = maxn;  // valid task seg we can insert without idle
        for (int i = 0; i < n; i++)
        {
            L = max(L+1, segs[i].l);
            R = min(R+1, segs[i].r);
            if (L >= R) // no slot to insert a task seg
            {
                cnt++;
                L = segs[i].l, R = segs[i].r;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
