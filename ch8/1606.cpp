// UVa 1606 Amphiphilic Carbon Molecules
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn = 1005;
int n, color[maxn];

struct Point
{
    int x, y;
    double rad;
    bool operator <(const Point &rhs) const { return rad < rhs.rad; }
}p[maxn], q[maxn];

// move A to B is counter clockwise while A.rad < B.rad
bool counter_clockwise(Point A, Point B) { return A.x * B.y >= A.y * B.x; }

int solve()
{
    if (n <= 2) return 2;
    int maxcnt = 0;
    // set p[i] as pivot point
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {   // two sides S1, S2, cnt = S0c0 + S1c1, so move Sic1 to S(i^1) and cnt = Si(C0+c1)
                q[k].x = color[j] ? p[i].x - p[j].x : p[j].x - p[i].x;
                q[k].y = color[j] ? p[i].y - p[j].y : p[j].y - p[i].y;
                q[k].rad = atan2(q[k].y, q[k].x);
                k++;
            }
        }
        sort(q, q+k); // sort by rad
        int L = 0, R = 0, cnt = 2;
        while (L < k)
        {
            if (R == L) R = (R+1)%k, cnt++;
            while (R != L && counter_clockwise(q[L], q[R])) // scan all points on the same side
                R = (R+1)%k, cnt++;
            cnt--, L++, maxcnt = max(maxcnt, cnt);
        }
    }
    return maxcnt;
}


int main()
{
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y >> color[i];
        cout << solve() << endl;
    }
    return 0;
}
