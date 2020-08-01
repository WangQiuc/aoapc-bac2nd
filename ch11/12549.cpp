// UVa 12549 Sentry Robots
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 105;
int n, m, r, c;
struct Node { int r, c; } nodes[maxn][maxn];    // nodes[i][j], mat[i][j]'s row and col
int match[maxn*maxn], mat[maxn][maxn];
vector<int> G[maxn*maxn];
bool vis[maxn*maxn];

int dfs(int x)
{
    for(int y : G[x]) if(!vis[y])
    {
        vis[y] = true;
        if(match[y] == -1 || dfs(match[y]))
        {
            match[x] = y;
            match[y] = x;
            return 1;
        }
    }
    return 0;
}

int hungarian()
{
    int cnt = 0;
    memset(match, -1, sizeof(int)*c);
    for(int i = 0; i <= r; i++) if(match[i] == -1)
    {
        memset(vis, 0, sizeof(int)*c);
        cnt += dfs(i);
    }
    return cnt;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m;
        memset(mat, 0, sizeof(mat));
        int t, x, y;
        cin >> t;
        while(t--)  // read points of interest
        {
            cin >> x >> y;
            mat[--x][--y] = 1;
        }
        cin >> t;
        while(t--)  // read obstacles
        {
            cin >> x >> y;
            mat[--x][--y] = -1;
        }
        r = -1;     // Row set [0, r] 
        for(int i = 0; i < n; i++)
        {
            bool first = true;
            for(int j = 0; j < m; j++)
            {
                if(mat[i][j] == 1)
                {
                    if(first) r++, first = false;
                    nodes[i][j].r = r;
                }
                if(mat[i][j] == -1) first = true;   // meet obstacle, break row
            }
        }
        c = ++r;     // Col set [r+1, c]
        for(int j = 0; j < m; j++)
        {
            bool first = true;
            for(int i = 0; i < n; i++)
            {
                if(mat[i][j] == 1)
                {
                    if(first) c++, first = false;
                    nodes[i][j].c = c;
                }
                if(mat[i][j] == -1) first = true;   // meet obstacle, break row
            }
        }
        c++;
        for(int i = 0; i <= r; i++) 
            G[i].clear();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) if(mat[i][j] == 1) 
                G[nodes[i][j].r].push_back(nodes[i][j].c);
        // bipartite maximum matching between Row set and Col set
        cout << hungarian() << endl;
    }
    return 0;
}
