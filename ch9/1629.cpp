// UVa 1629 Cake Slicing
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 25, INF = maxn*maxn;

int d[maxn][maxn][maxn][maxn];
bool a[maxn][maxn];

int check(int x0, int y0, int x1, int y1)
{
    int cnt = 0;
    for (int i = x0; i <= x1; i++)
        for (int j = y0; j <= y1; j++)
            if ((cnt += a[i][j]) > 1) return 2;   
    return cnt;
}

int dp(int x0, int y0, int x1, int y1)
{
    int &ans = d[x0][y0][x1][y1];
    if (ans != -1) return ans;
    int state = check(x0, y0, x1, y1);
    if (state == 1) return ans = 0;     // no need to further cut
    ans = INF;
    if (!state) return ans;
    for (int x = x0; x <= x1; x++)      // cut vertically at x
        ans = min(ans, dp(x0,y0,x,y1)+dp(x+1,y0,x1,y1)+y1-y0+1);
    for (int y = y0; y <= y1; y++)      // cut horizontally at y
        ans = min(ans, dp(x0,y0,x1,y)+dp(x0,y+1,x1,y1)+x1-x0+1);
    return ans;
}

int main()
{
    int r, c, n, x, y, kase = 0;
    while (cin >> r >> c >> n)
    {
        memset(d, -1, sizeof(d));
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            a[x-1][y-1] = true;
        }
        cout << "Case " << ++kase << ": " << dp(0,0,r-1,c-1) << endl;
    }
    return 0;
}
