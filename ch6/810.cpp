// UVa810 A Dicey Problem
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

const int maxn = 10;
int dice[7][7], b[maxn][maxn], R, C, X, Y, T, F;
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
bool v[maxn][maxn][7][7];
vector<int> path;

void build_dice()       // dice[top][front] = right
{
    dice[1][2] = 3, dice[1][3] = 5, dice[1][4] = 2, dice[1][5] = 4,
    dice[2][1] = 4, dice[2][3] = 1, dice[2][4] = 6, dice[2][6] = 3,
    dice[3][1] = 2, dice[3][2] = 6, dice[3][5] = 1, dice[3][6] = 5,
    dice[4][1] = 5, dice[4][2] = 1, dice[4][5] = 6, dice[4][6] = 2,
    dice[5][1] = 3, dice[5][3] = 6, dice[5][4] = 1, dice[5][6] = 4,
    dice[6][2] = 4, dice[6][3] = 2, dice[6][4] = 5, dice[6][5] = 3;
}

bool valid(int x, int y) { return x >= 0 && x < R && y >= 0 && y < C; }

void rotate(int t0, int f0, int &t, int &f, int d)
{
    if (d == 0) { t = f0, f = 7 - t0; }
    if (d == 1) { t = 7 - f0, f = t0; }
    if (d == 2) { t = dice[t0][f0], f = f0; }
    if (d == 3) { t = 7 - dice[t0][f0], f = f0; }
}

bool dfs(int x0, int y0, int t0, int f0)
{   
    int x, y, t, f;  
    for (int i = 0; i < 4; i++)
    {
        x = x0 + dx[i], y = y0 + dy[i], rotate(t0, f0, t, f, i);
        if (valid(x, y) && !v[x][y][t][f] && (b[x][y] == t0 || b[x][y] == -1))
        {
            path.push_back(x * 10 + y);
            v[x][y][t][f] = true;
            if ((x == X && y == Y) || dfs(x, y, t, f)) return true;
            v[x][y][t][f] = false;
            path.pop_back();
        }
    }
    return false;
}

int main()
{
    build_dice();
    string s;
    while (cin >> s && s != "END")
    {
        cout << s << endl << "  ";
        cin >> R >> C >> X >> Y >> T >> F;
        memset(b, 0, sizeof(b));
        memset(v, 0, sizeof(v));
        path.clear(); path.push_back(--X * 10 + --Y);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                cin >> b[i][j];
        if (dfs(X, Y, T, F))
        {
            int cnt = 0, n = path.size() - 1;
            for (int i = 0; i < n; i++)
            {
                cout << "(" << path[i] / 10 + 1 << "," << path[i] % 10 + 1 << "),";
                if (!(++cnt % 9)) cout << endl << "  ";
            }
            cout << "(" << path[n] / 10 + 1 << "," << path[n] % 10 + 1 << ")\n";
        }
        else cout << "No Solution Possible\n";
    }
    return 0;
}
