// UVa 11400 Lighting System Design
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 1005;

struct Lamp
{
    int v, k, c, l;
    bool operator < (const Lamp &rhs) const { return v < rhs.v; }
} lamp[maxn];

int n, s[maxn], dp[maxn];

int main()
{
    while (cin >> n && n)
    {
        for (int i = 1; i <= n; i++)
            cin >> lamp[i].v >> lamp[i].k >> lamp[i].c >> lamp[i].l;
        sort(lamp+1, lamp+n+1);
        s[0] = dp[0] = 0;
        for (int i = 1; i <= n; i++)
            s[i] = s[i-1] + lamp[i].l;
        for (int i = 1; i <= n; i++)
        {   // all in lamp i
            dp[i] = s[i]*lamp[i].c + lamp[i].k;
            for (int j = 1; j < i; j++) 
                dp[i] = min(dp[i], dp[j] + (s[i]-s[j])*lamp[i].c + lamp[i].k); // j ~ i in lamp i
        }
        cout << dp[n] << endl;
    }
    return 0;
}
