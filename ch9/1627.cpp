// UVa 1627 Team them up
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn = 105;
int n, cc, G[maxn][maxn], color[maxn], diff[maxn];
bool d[maxn][maxn*2];
vector<int> team[maxn][2];

// bipartite
bool dfs(int x, int c)
{
    color[x] = c;
    team[cc][c-1].push_back(x);
    for (int y = 0; y < n; y++) if (x != y && !(G[x][y] && G[y][x]))
    {
        if (color[y] && color[x] == color[y]) return false;
        if (!color[y] && !dfs(y, 3-c)) return false;
    }
    return true;
}

bool build()
{
    memset(color, 0, sizeof(color));
    cc = 0;
    for (int i = 0; i < n; i++) if (!color[i])
    {
        team[cc][0].clear();
        team[cc][1].clear();
        if (!dfs(i, 1)) return false;
        diff[cc] = team[cc][0].size() - team[cc][1].size();
        cc++;
    }
    return true;
}

void print(int ans)
{
    vector<int> t1, t2;
    for (int i = cc-1; i >= 0; i--)
    {
        int t;
        if (d[i][ans-diff[i]+n]) t = 0, ans -= diff[i];
        else t = 1, ans += diff[i];
        for (int x : team[i][t]) t1.push_back(x);
        for (int x : team[i][t^1]) t2.push_back(x);
    }
    cout << t1.size();
    for (int x : t1) cout << " " << x+1;
    cout << endl;
    cout << t2.size();
    for (int x : t2) cout << " " << x+1;
    cout << endl;
}

void dp()
{
    memset(d, 0, sizeof(d));
    d[0][n] = 1;
    for (int i = 0; i < cc; i++)
        for (int j = -n; j <= n; j++) if (d[i][j+n])
            d[i+1][j+diff[i]+n] = d[i+1][j-diff[i]+n] = true;
    for (int ans = 0; ans <= n; ans++)
    {
        if (d[cc][n+ans]) {print(ans); return; }
        if (d[cc][n-ans]) {print(-ans); return; }
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        memset(G, 0, sizeof(G));
        for (int x = 0; x < n; x++)
        {
            int y;
            while (cin >> y && y) G[x][y-1] = 1;
        }
        if (!build()) cout << "No solution\n";
        else dp();
        if (T) cout << endl;
    }
    return 0;
}
