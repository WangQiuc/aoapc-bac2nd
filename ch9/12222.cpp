// UVa 12222 Mountain Road
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 205, inf = 0x3f3f3f3f;
// dp[i][j][p] a(left end)'s ith car and b(right end)'s jth car, p: 0-a, 1-b
int dp[maxn][maxn][2];

struct Car
{   // arrival time, minimal finish time
    int t, d;
} a[maxn], b[maxn];

int main()
{
    int n, T, na, nb;
    cin >> T;
    while(T--)
    {
        cin >> n;
        na = nb = 0;
        for(int i = 1; i <= n; i++)
        {
            char c; cin >> c;
            if(c == 'A') cin >> a[++na].t >> a[na].d;
            else cin >> b[++nb].t >> b[nb].d;
        }
        memset(dp, inf, sizeof(dp));
        dp[0][0][0] = dp[0][0][1] = 0;
        for(int i = 0; i <= na; i++)
            for(int j = 0; j <= nb; j++)
            {
                int s = dp[i][j][0], e = 0;
                for(int k = i+1; k <= na; k++)  // drive k cars at end 0/1
                {   // faster car needs to wait slower car in the front
                    s = max(s, a[k].t);
                    e = max(e, s+a[k].d);
                    dp[k][j][1] = min(dp[k][j][1], e);
                    s += 10, e += 10;
                }
                s = dp[i][j][1], e = 0;
                for(int k = j+1; k <= nb; k++)
                {
                    s = max(s, b[k].t);
                    e = max(e, s+b[k].d);
                    dp[i][k][0] = min(dp[i][k][0], e);
                    s += 10, e += 10;
                }
            }
        cout << min(dp[na][nb][0], dp[na][nb][1]) << endl;
    }
    return 0;
}
