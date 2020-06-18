// UVa 1631 Locker
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1005;
const int INF = 0x3fffffff;

char s1[maxn], s2[maxn];
int n, a1[maxn], a2[maxn], d[maxn][10][10][10];

int dp(int i, int x1, int x2, int x3)
{
    if (i >= n) return 0;
    int &ans = d[i][x1][x2][x3];
    if (ans != -1) return ans;
    ans = INF;
    int t = (a2[i]-x1+10) % 10;   // rotate upwards
    for (int j = 0; j <= t; j++)
        for (int k = 0; k <= j; k++)
            ans = min(ans, dp(i+1, (x2+j)%10, (x3+k)%10, a1[i+3]) + t);
    t = (x1-a2[i]+10) % 10;       // rotate downwards
    for (int j = 0; j <= t; j++)
        for (int k = 0; k <= j; k++)
            ans = min(ans, dp(i+1, (x2-j+10)%10, (x3-k+10)%10, a1[i+3]) + t);
    return ans;
}

int main()
{
    while (cin >> s1 >> s2)
    {
        memset(d, -1, sizeof(d));
        n = strlen(s1);
        for (int i = 0; i < n; i++)
            a1[i] = s1[i]-'0', a2[i] = s2[i]-'0';
        a1[n] = a1[n+1] = a2[n] = a2[n+1] = 0;
        cout << dp(0, a1[0], a1[1], a1[2]) << endl;
    }
    
    return 0;
}
