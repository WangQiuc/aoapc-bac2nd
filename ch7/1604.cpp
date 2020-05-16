// UVa 1604 Cubic Eight Puzzle
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

struct Node { int top, front; };
const char *color = "EWRB";
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
int x0, y0, mind, target[3][3];
Node node[3][3];

int h()
{
    int cost = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cost += node[i][j].top != target[i][j];
    return cost;
}

void move(int x, int y, bool v)
{   // vertical move
    if (v) swap(node[x][y].top, node[x][y].front);
    else node[x][y].top ^= node[x][y].front;    // c1 ^ c2 = c3
    swap(node[x0][y0], node[x][y]);
    x0 = x, y0 = y;
}

void dfs(int px, int py, int d)
{
    int cost = h();
    if (!cost) { mind = min(mind, d); return; }
    if (mind - d < cost) return;
    int tx = x0, ty = y0;   //  global x0, y0 will change after move() so need to store them first
    for (int i = 0; i < 4; i++)
    {
        int x = x0 + dx[i], y = y0 + dy[i];
        if (0 <= x && x < 3 && 0 <= y && y < 3 && (x != px || y != py)) // don't move back
        {
            move(x, y, i<2);
            dfs(tx, ty, d+1);
            move(tx, ty, i<2);  // move back, 0<->1, 2<->3
        }
    }
}

int main()
{
    char c;
    while (cin >> y0 >> x0 && y0)
    {
        x0--, y0--;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                cin >> c;
                target[i][j] = strchr(color, c) - color;
                node[i][j].top = 1, node[i][j].front = 2;
            }
        node[x0][y0].top = node[x0][y0].front = 0;
        mind = 31;
        dfs(-1, -1, 0);
        cout << (mind > 30 ? -1 : mind) << endl;
    }
    return 0;
}
