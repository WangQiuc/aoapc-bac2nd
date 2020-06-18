// UVa 10285 Longest Run on a Snowboard
// wangqc
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

const int maxn = 102;
const int di[] = {-1,1,0,0}, dj[] = {0,0,-1,1};

int r, c, a[maxn][maxn], d[maxn][maxn];

inline bool valid(int i, int j) { return 0 <= i && i < r && 0 <= j && j < c; }

int dfs(int i0, int j0)
{
    int &ans = d[i0][j0];
    if (ans) return ans;
    ans = 1;
    for (int i, j, dir = 0; dir < 4; dir++)
        if (valid((i=i0+di[dir]), (j=j0+dj[dir])) && a[i][j] < a[i0][j0])
            ans = max(ans, dfs(i,j) + 1);
    return ans;
}

int main()
{
    int T;
    string name;
    cin >> T;
    while (T--)
    {
        cin >> name >> r >> c;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> a[i][j];
        memset(d, 0, sizeof(d));
        int ans = 1;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                ans = max(ans, dfs(i, j));
        cout << name << ": " << ans << endl;
    }
    return 0;
}
