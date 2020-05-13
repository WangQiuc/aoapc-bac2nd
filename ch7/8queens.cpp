// wangqc

#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 20;
int n, cnt, row[maxn];
bool vis[3][maxn << 1];

void dfs(int cur)
{
    if (cur == n) cnt++;
    else for (int i = 0; i < n; i++)
    {
        if (!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n])
        {
            row[cur] = i;
            vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = true;
            dfs(cur + 1);
            vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = false;
        }
    }
}

int main()
{
    while (cin >> n && n)
    {
        cnt = 0;
        memset(row, 0, sizeof(row));
        memset(vis, 0, sizeof(vis));
        dfs(0);
        cout << n << " queens solutions' count: " << cnt << endl;
    }
}