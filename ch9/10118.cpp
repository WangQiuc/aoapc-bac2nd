// UVa 10118 Free Candies
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 45;
int n, p[4][maxn], idx[4], d[maxn][maxn][maxn][maxn];

int dp(int s, int cnt)
{
    if (cnt == 5) return 0;
    int &ans = d[idx[0]][idx[1]][idx[2]][idx[3]];
    if (ans != -1) return ans;
    ans = 0;
    for (int i = 0; i < 4; i++) if (idx[i] < n)
    {
        int hit = (s >> p[i][idx[i]]) & 1, s2 = s ^ (1 << p[i][idx[i]]);
        idx[i]++;
        ans = max(ans, dp(s2, cnt+1-(hit<<1)) + hit);
        idx[i]--;
    }
    return ans;
}

int main()
{
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 4; j++)
                cin >> p[j][i];
        memset(idx, 0, sizeof(idx));
        memset(d, -1, sizeof(d));
        cout << dp(0, 0) << endl;
    }
    return 0;
}
