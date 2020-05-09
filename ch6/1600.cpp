// UVa1600 Patrol Robot
// wangqc
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;  

const int maxn = 25;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int m, n, K, board[maxn][maxn], kcnt[maxn][maxn];

struct Node
{
    int x, y, d, k;
    Node(int x, int y, int d, int k): x(x), y(y), d(d), k(k) {};
};

int bfs()
{
    if (m == 1 && n == 1) return 0;
    queue<Node> q;
    memset(kcnt, maxn*maxn, sizeof(kcnt));
    q.push(Node(0, 0, 0, 0));
    while (!q.empty())
    {
        Node node = q.front(); q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = node.x + dx[i], y = node.y + dy[i], d = node.d + 1;
            if (x == m - 1 && y == n - 1) return d;
            if (x >= 0 && x < m && y >= 0 && y < n)
            {
                int k = board[x][y] ? node.k + 1 : 0;
                if (k >= kcnt[x][y] || k > K) continue;
                kcnt[x][y] = k;
                q.push(Node(x, y, d, k));
            }
        }
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> m >> n >> K;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> board[i][j];
        cout << bfs() << endl;
    }
    return 0;
}
