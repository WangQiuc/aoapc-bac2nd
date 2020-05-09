// UVa439 Knight Moves
// wangqc
# include<iostream>
# include<cstring>
# include<queue>

using namespace std;  

const int dx[] = {-2, -2, -1, -1,  1,  1,  2, 2};
const int dy[] = {-1,  1, -2,  2, -2,  2, -1, 1};
int x0, y0, x1, y1, board[8][8];

int bfs()
{
    if (x0 == x1 && y0 == y1) return 0;
    queue<int> q;
    q.push(x0 | y0 << 3);
    board[x0][y0] = 0;
    while (!q.empty())
    {
        x0 = q.front() & 7, y0 = q.front() >> 3; q.pop();
        for (int i = 0; i < 8; i++)
        {
            int x = x0 + dx[i], y = y0 + dy[i], d = board[x0][y0] + 1;
            if (x == x1 && y == y1) return d;
            if (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == -1)
            {
                board[x][y] = d;
                q.push(x | y << 3);
            }
        }
    }
    return -1;
}

int main()
{
    string s0, s1;
    while (cin >> s0 >> s1)
    {
        memset(board, -1, sizeof(board));
        x0 = s0[0] - 'a', y0 = s0[1] - '1';
        x1 = s1[0] - 'a', y1 = s1[1] - '1';
        cout << "To get from " << s0 << " to " << s1 << " takes " << bfs() << " knight moves.\n";
    }
    return 0;
}
