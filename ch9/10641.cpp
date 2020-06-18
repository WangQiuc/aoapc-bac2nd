// UVa 10641 Barisal Stadium
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
int n, m, dp[70];
bool vis[35];

struct Point {       // vertex coordinate
    double x, y;
} v[35];

struct Seg {         // light position with cost that can cover points[i:j]
    int i, j, cost;
    Seg(int i=0, int j=0, int cost=0): i(i), j(j), cost(cost) {}
} p[1005];

// position p can cover vertices v1 and v2, cross product
bool cover(Point p, Point v1, Point v2)
{
    return (v2.y-p.y)*(v1.x-p.x) - (v1.y-p.y)*(v2.x-p.x) < -eps;
}

Seg gen_seg(Point pos, int k)
{
    for(int i = 0; i < n; i++)
        vis[i] = cover(pos, v[i], v[i+1]);
    int i, j;
    if(vis[0] && vis[n-1])
    {
        i = n-1, j = 0;
        while(vis[i-1]) i--;
        while(vis[j+1]) j++;
        j += n;
    }
    else
    {
        i = 0, j = n-1;
        while(!vis[i]) i++;
        while(!vis[j]) j--;
    }
    return Seg(i, j+1, k);
}

int main()
{
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            cin >> v[i].x >> v[i].y;
        v[n] = v[0];
        cin >> m;
        Point pos;
        int k;
        for (int i = 0; i < m; i++)
        {
            cin >> pos.x >> pos.y >> k;
            p[i] = gen_seg(pos, k);
        }
        int ans = INF;
        for (int offset = 0; offset < n; offset++)
        {
            memset(dp, INF, sizeof(dp));
            dp[offset] = 0;
            for (int i0 = 0; i0 < n; i0++)
            {
                int i = i0 + offset;
                for (int k = 0; k < m; k++) if (p[k].i <= i)
                    dp[p[k].j] = min(dp[p[k].j], dp[i]+p[k].cost);
            }
            ans = min(ans, dp[offset+n]);
        }
        if (ans == INF) cout << "Impossible.\n";
        else cout << ans << endl;
    }
    return 0;
}
