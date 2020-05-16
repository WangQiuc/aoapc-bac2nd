// UVa 225 Golygons
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int maxc = 20;
const int offset = 60;  // rotate 90 each time, 10∑(i*2) / 2 = 55;
const int maxn = offset << 1;  // rotate 90 each time, 10∑(i*2) / 2 = 55;
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
const char *dirs = "ensw";     // lexicographic order (0,3)<->(1,2)
char path[offset];
bool vis[maxn][maxn], block[maxn][maxn];
int n, cnt, dist[maxc+1];

bool valid(int x, int y, int d, int k) 
{ 
    
    if (k > n || 0 > x || x > maxn || 0 > y || y > maxn || vis[y][x]) return false;
    if (abs(x - offset) + abs(y - offset) > dist[n] - dist[k]) return false;
    while (k--)
    {
        if (block[y][x]) return false;
        x -= dx[d], y -= dy[d];
    }
    return true; 
}

void dfs(int x0, int y0, int d0, int k)  // kth iteration, move k steps
{
    int x = x0 + k*dx[d0], y = y0 + k*dy[d0];
    if (valid(x, y, d0, k))
    {
        path[k] = dirs[d0];
        if (k == n && x == offset && y == offset)
        {
            for (int i = 1; i <= k; i++)
                cout << path[i];
            cout << endl;
            cnt++;
        }
        else
        {
            vis[y][x] = true;
            dfs(x, y, 1 - (!dx[d0]), k+1);  // d0 == (n, s) ? e : n
            dfs(x, y, 2 + (!dx[d0]), k+1);  // d0 == (n, s) ? w : s   
            vis[y][x] = false;
        }
    }
}

int main()
{
    dist[0] = 0;
    for (int i = 1; i <= maxc; i++)
        dist[i] += dist[i-1] + i;
    int T, m;
    cin >> T;
    while(T--)
    {
        cin >> n >> m;
        memset(vis, 0, sizeof(vis));
        memset(block, 0, sizeof(block));
        cnt = 0;
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            block[offset+y][offset+x] = true;
        }
        for (int d = 0; d < 4; d++)
            dfs(offset, offset, d, 1);
        cout << "Found " << cnt << " golygon(s).\n\n";
    }
    return 0;
}
