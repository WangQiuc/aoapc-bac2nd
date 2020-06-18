// UVa 12093 Protecting Zonk
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 10005, INF = 1<<30;
int n, c1, c2, f[maxn][4];
vector<int> tree[maxn];

void dfs(int x, int p)
{
    f[x][0] = f[x][1] = f[x][3] = 0, f[x][2] = c2;
    int c3 = INF; // alternative for installing a c1: intalling a c2 at any child
    for (int y : tree[x]) if (y != p)
    {
        dfs(y, x);
        f[x][0] += min(f[y][1], f[y][2]);
        int t = min(f[y][0], min(f[y][1], f[y][2]));
        f[x][1] += t;
        f[x][2] += min(t, f[y][3]);
        f[x][3] += t;
        c3 = min(c3, f[y][2]-t);
    }
    f[x][1] += min(c1, c3);
}

int main()
{
    while(cin >> n >> c1 >> c2 && n)
    {
        for (int i = 1; i <= n; i++)
            tree[i].clear();
        memset(f, 0, sizeof(f));
        for (int i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            tree[x].push_back(y);
            tree[y].push_back(x);
        }
        dfs(1, -1);
        cout << min(min(f[1][0], f[1][1]), f[1][2]) << endl;
    }
    return 0;
}
