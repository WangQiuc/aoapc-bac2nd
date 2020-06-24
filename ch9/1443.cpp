// UVa 1443 Garlands
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 40005, inf = 1<<30;
int n, m, k, d, ans, cnt;
// seg length needs to be even, so some segs in a[i-1] can't be covered in a[i], but can be covered in a[i-2]
int psum[maxn], dp[maxn][2];    

bool valid(int x)
{
    for(int i = 0; i <= n; i++) 
        dp[i][0] = dp[i][1] = inf;
    dp[0][0] = 0;
    for(int i = 2; i <= n; i+=2)
        for(int k = 1; k <= min(d, i>>1); k++)
        {
            if (psum[i]-psum[i-k] > x) break;
            int j = i-(k<<1);
            if (psum[i-k]-psum[j] > x) continue;
            dp[i][0] = min(dp[i][0], dp[j][1]+1);
            dp[i][1] = min(dp[i][1], dp[j][0]+1);
        }
    return dp[n][m&1] <= m;
}

int main()
{
    int x, T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m >> d;
        psum[0] = 0, m--;
        for(int i = 1; i <= n; i++)
        {
            cin >> x;
            psum[i] = psum[i-1] + x;
        }
        if(n & 1 || n < m<<1 || n > (m*d)<<1)
        {   cout << "BAD\n"; continue; }
        int lo = 1, hi = psum[n];
        while (lo < hi)
        {
            x = (lo + hi) >> 1;
            if(valid(x)) hi = x;
            else lo = x + 1;
        }
        cout << lo << endl;
    }
    return 0;
}
