// UVa 1634 The Picnic
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 105, inf = 0x3f3f3f3f;
int n, m, ans, dp[maxn][maxn];
struct Point
{
    int x, y;
    Point(int x=0, int y=0): x(x), y(y) {}
    Point operator - (const Point &rhs) const { return Point(x-rhs.x, y-rhs.y); }
    bool operator < (const Point &rhs) const;
}points[maxn], origin, usable[maxn];

int crossproduct(const Point &a, const Point &b) { return a.x*b.y - b.x*a.y;  }

int dist(const Point &a) { return a.x*a.x + a.y*a.y; }

// rank point in counterclockwise order
bool Point::operator < (const Point &rhs) const
{
    int cp = crossproduct(*this-origin, rhs-origin);
    if (cp) return cp > 0;
    return dist(*this-origin) < dist(rhs-origin);
}

void solve()
{
    memset(dp, 0, sizeof(dp));
    sort(usable+1, usable+m+1);
    for (int i = 2; i <= m; i++)
    {
        int j = i-1;
        while(j && !crossproduct(usable[i]-origin, usable[j]-origin)) j--;
        bool unaligned = j == i-1;  // not on the same line
        while(j)
        {
            int k = j-1;
            // i-j-k is a convex when crossproduct(ik, jk) > 0
            while (k && crossproduct(usable[i]-usable[k], usable[j]-usable[k]) > 0) k--;
            int area = abs(crossproduct(usable[i]-origin, usable[j]-origin));
            if (k) area += dp[j][k];
            if (unaligned) dp[i][j] = area;
            ans = max(ans, area);
            j = k;
        }
        if (unaligned)
            for (int j = 2; j < i; j++)
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> points[i].x >> points[i].y;
        ans = 0;
        for (int i = 0; i < n; i++)
        {
            origin = points[i];
            m = 0;
            for (int j = 0; j < n; j++)
                if (points[j].y > origin.y || (points[j].y == origin.y && points[j].x > origin.x))
                    usable[++m] = points[j];
            solve();
        }
        printf("%.1lf\n", 0.5*ans);
    }
    return 0;
}
