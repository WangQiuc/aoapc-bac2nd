// UVa 11694 Gokigen Naname
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

int const maxn = 10;
int n, grid[maxn][maxn], p[maxn*maxn];  // use disjoint set to detect cycle
char buf[maxn][maxn] ;         // output

int find (int u)
{
    return p[u] == u ? u : find(p[u]);
}

// as we iterate from left to right, top to bottom, only '/' would form a cycle, 
// top left intersect at most hold 1 more line if place '\' or 0 line if place a '/'
bool dfs(int x, int y)    
{
    if (x == n-1)    // last row, each cell should be balanced (negative or 0)
    {
        for (int i = 0; i < n; i++) 
            if (grid[x][i] > 0) return false;
        for (int i = 0; i < n-1; i++)
        {
            for (int j = 0; j < n-1; j++) cout << buf[i][j];
            cout << endl;
        }
        return true;
    }
    if (y == n-1)    // last colume
    {
        if (grid[x][y] > 0) return false;
        return dfs(x+1, 0);
    }
    // u - top left, v - bottom left, u+1 - top right, v+1 - bottom right
    int u = x * n + y, v = u + n, pu, pv;
    if ((grid[x][y] < 0 || grid[x][y] == 1) && grid[x+1][y+1])
    {
        pu = find(u), pv = find(v+1);
        buf[x][y] = '\\', grid[x][y]--, grid[x+1][y+1]--, p[pu] = pv;
        if (dfs(x, y+1)) return true;
        grid[x][y]++, grid[x+1][y+1]++, p[pu] = pu;
    }       
    if (grid[x][y] <= 0 && grid[x+1][y] && grid[x][y+1] && (pu=find(u+1)) != (pv=find(v)))  
    {
        buf[x][y] = '/', grid[x+1][y]--, grid[x][y+1]--, p[pu] = pv;
        if (dfs(x, y+1)) return true;
        grid[x+1][y]++, grid[x][y+1]++, p[pu] = pu;
    }
    return false;                      
}

int main()
{
    int T; char x;
    cin >> T;
    while (T--)
    {
        cin >> n; n++;      // n cells, n+1 intersections
        memset(grid, -1, sizeof(grid));  // negative value as wildcard (no limit)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (cin >> x && x != '.') grid[i][j] = x - '0';
        for (int i = 0; i <= n * n; i++)
            p[i] = i;
        dfs(0, 0);
    }
    return 0;
}
