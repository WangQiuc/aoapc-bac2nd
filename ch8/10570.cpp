// UVa 10570 Meeting with Aliens
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 505 << 1;
int n, a[maxn];
bool vis[maxn];

void dfs(int x, int offset)         // clockwise cycle
{
    vis[x] = true;
    int y = a[offset + x];
    if (!vis[y]) dfs(y, offset);
}

void dfs_rev(int x, int offset)     // counter-clockwise cycle
{
    vis[x] = true;
    int y = a[offset - x];
    if (!vis[y]) dfs_rev(y, offset);
}

int main()
{
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            a[i + n] = a[i];        // max offset = n;
        }
        int maxcnt = 0, cnt;
        for (int offset = 0; offset < n; offset++)
        {
            memset(vis, 0, sizeof(vis));
            cnt = 0;
            for (int i = 0; i < n; i++) if (!vis[i])
            {
                dfs(i, offset);
                cnt++;
            }
            maxcnt = max(maxcnt, cnt);
        }
        for (int offset = 2*n-1; offset >= n; offset--)
        {
            memset(vis, 0, sizeof(vis));
            cnt = 0;
            for (int i = 0; i < n; i++) if (!vis[i])
            {
                dfs_rev(i, offset);
                cnt++;
            }
            maxcnt = max(maxcnt, cnt);
        }
        cout << n - maxcnt << endl;  
    }
    return 0;
}
