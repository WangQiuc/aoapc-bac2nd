// UVa 11882 Biggest Number
// wangqc
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

const int maxn = 15;
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
int r, c;
string maxs;
char p[maxn][maxn], vals[maxn*maxn];
bool vis[maxn][maxn];
bool larger(string a, string b) { return a.size() > b.size() || (a.size() == b.size() && a > b); }
bool valid(int x, int y) { return 0 <= x && x < r && 0 <= y && y < c && p[x][y] != '#'; }

int bfs(int x, int y)     // return max # nodes can still be reached from (x0, y0)
{
    bool mark[maxn][maxn];
    memcpy(mark, vis, sizeof(mark));
    queue<int> q;
    q.push(x*c + y);
    int cnt = 0;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int i = 0; i < 4; i++)
        {
            x = u/c + dx[i], y = u%c + dy[i];
            if (valid(x, y) && !mark[x][y])
            {
                mark[x][y] = true;
                vals[cnt++] = p[x][y];
                q.push(x*c + y);
            }
        }
    }
    return cnt;
}

void dfs(int x0, int y0, string s)
{
    if (larger(s, maxs)) maxs = s;
    else    // pruning
    {
        int cnt = bfs(x0, y0);
        if (s.size() + cnt < maxs.size()) return;
        if (s.size() + cnt == maxs.size())
        {
            sort(vals, vals+cnt);
            string t = s;
            while (cnt) t += vals[--cnt];
            if (!larger(t, maxs)) return; 
        }
    }
    for (int i = 0; i < 4; i++)
        {
            int x = x0 + dx[i], y = y0 + dy[i];
            if (valid(x, y) && !vis[x][y])
            {
                vis[x][y] = true;
                dfs(x, y, s+p[x][y]);
                vis[x][y] = false;
            }
        }
}

int main()
{
    while (scanf("%d %d", &r, &c) && r)
    {
        maxs.clear();
        for (int i = 0; i < r; i++)
            scanf("%s", p[i]);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) if (p[i][j] != '#')
            {
                memset(vis, 0, sizeof(vis));
                vis[i][j] = true;
                string s = "";
                s += p[i][j];
                dfs(i, j, s);
            }
        printf("%s\n", maxs.c_str());
    }
    return 0;
}
