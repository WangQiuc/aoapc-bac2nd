// UVa 10384 The Wall Pushers
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const char *dirs = "WNES";
const int dx[] = {0,-1,0,1};
const int dy[] = {-1,0,1,0};
int maxd, graph[4][6], seq[30];
bool vis[4][6];

bool valid(int x, int y) { return 0 <= x && x < 4 && 0 <= y && y < 6; }

int check(int x, int y)
{
    if (y == 0 && !(graph[x][y] & 1)) return 0;  // west exit
    if (x == 0 && !(graph[x][y] & 2)) return 1;  // north exit
    if (y == 5 && !(graph[x][y] & 4)) return 2;  // east exit
    if (x == 3 && !(graph[x][y] & 8)) return 3;  // south exit
    return -1;
}

bool dfs(int x0, int y0, int d)
{
    if (d == maxd)
    {
        int i = check(x0, y0);
        if (i == -1) return false;
        seq[d] = i;  
        return true;
    }
    for (int i = 0; i < 4; i++)
    {
        int x = x0 + dx[i], y = y0 + dy[i];
        if (valid(x, y) && !vis[x][y])
        {
            if (!(graph[x0][y0] & 1<<i))
            {   
                vis[x][y] = true;
                seq[d] = i;
                if (dfs(x, y, d+1)) return true;
                vis[x][y] = false;
            }
            else if (!(graph[x][y] & 1<<i))    // push wall
            {   // add a inner wall at reversed direction for neighbor cell
                if (valid(x+dx[i], y+dy[i])) graph[x+dx[i]][y+dy[i]] += 1<<(i^2);    
                graph[x0][y0] -= 1<<i, graph[x][y] += 1<<i, vis[x][y] = true;
                seq[d] = i;
                if (dfs(x, y, d+1)) return true;
                graph[x0][y0] += 1<<i, graph[x][y] -= 1<<i, vis[x][y] = false;
                if (valid(x+dx[i], y+dy[i])) graph[x+dx[i]][y+dy[i]] -= 1<<(i^2);   
            }
        }
    }
    return false;
}

int main()
{
    int x, y;
    while (cin >> y >> x && y)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 6; j++)
             cin >> graph[i][j];
        x--, y--;
        for (maxd = 0; ;maxd++)
        {
            memset(vis, 0, sizeof(vis));
            vis[x][y] = true;
            if (dfs(x, y, 0))
            {
                for (int i = 0; i <= maxd; i++) 
                    cout << dirs[seq[i]];
                cout << endl;
                break;
            }
        }
    }
    return 0;
}
