// UVa 1601 The Morning after Halloween
// wangqc
#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>

using namespace std;

const int maxs = 20;
const int maxn = 150;
const int dx[] = {-1, 1, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0};
int s[3], t[3], deg[maxn], graph[maxn][5], dist[maxn][maxn][maxn];

inline int ID(int a, int b, int c)
{
    return (a << 16) | (b << 8) | c;
}
inline bool conflict(int a, int b, int a2, int b2)  // a move to a2, b move to b2
{
    return a2 == b2 || (a2 == b && b2 == a);
}

int bfs()
{
    queue<int> q;
    memset(dist, -1, sizeof(dist));
    q.push(ID(s[0], s[1], s[2]));
    dist[s[0]][s[1]][s[2]] = 0;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        int a = (u>>16)&0xff, b = (u>>8)&0xff, c = u&0xff;
        if (a == t[0] && b == t[1] && c == t[2]) return dist[a][b][c];
        for (int i = 0; i < deg[a]; i++)
        {
            int a2 = graph[a][i];
            for (int j = 0; j < deg[b]; j++)
            {
                int b2 = graph[b][j];
                if (conflict(a, b, a2, b2)) continue;
                for (int k = 0; k < deg[c]; k++)
                {
                    int c2 = graph[c][k];
                    if (conflict(a, c, a2, c2) || conflict(b, c, b2, c2) || (dist[a2][b2][c2] != -1)) 
                        continue; 
                    dist[a2][b2][c2] = dist[a][b][c] + 1;
                    q.push(ID(a2, b2, c2));
                }
            }
        }
    }
    return -1;
}

int main()
{
    int w, h, n;
    while (scanf("%d%d%d\n", &w, &h, &n) == 3 && n)
    {
        char maze[maxs][maxs];
        for (int i = 0; i < h; i++)
            fgets(maze[i], maxs, stdin);
        int cnt = 0, x[maxn], y[maxn], id[maxs][maxs];
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (maze[i][j] != '#')
                {
                    x[cnt] = i, y[cnt] = j, id[i][j] = cnt;
                    if (islower(maze[i][j])) s[maze[i][j] - 'a'] = cnt;
                    else if (isupper(maze[i][j])) t[maze[i][j] - 'A'] = cnt;
                    cnt++; 
                }
        for (int i = 0; i < cnt; i++)
        {
            deg[i] = 0;
            for (int d = 0; d < 5; d++)
            {
                int nx = x[i] + dx[d], ny = y[i] + dy[d];
                if (maze[nx][ny] != '#') graph[i][deg[i]++] = id[nx][ny];
            }
        }
        if (n <= 2) { deg[cnt] = 1; graph[cnt][0] = cnt; s[2] = t[2] = cnt++; }
        if (n <= 1) { deg[cnt] = 1; graph[cnt][0] = cnt; s[1] = t[1] = cnt++; }
        printf("%d\n", bfs());
    }
    return 0;
}
