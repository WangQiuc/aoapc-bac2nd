// UVa816 Abbott's Revenge
// wangqc

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 10;
const char *dirs = "NESW";
const char *turns = "FLR";
int dir(char c) { return strchr(dirs, c) - dirs; }
int turn(char c) { return strchr(turns, c) - turns; }
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
struct Node
{
    int r, c, d;
    Node() {}
    Node(int r, int c, int d): r(r), c(c), d(d) {}
};
int neigh[maxn][maxn][4][3];
int dist[maxn][maxn][4];
Node p[maxn][maxn][4];
int r0, c0, d1, r1, c1, r2, c2;

Node walk(const Node &x, int turn)
{
    int d = x.d;
    if (turn == 1) d = (d + 3) % 4;
    if (turn == 2) d = (d + 1) % 4;
    return Node(x.r + dr[d], x.c + dc[d], d);
}

bool valid(Node y)
{
    int r = y.r, c = y.c, d = y.d;
    return r >= 1 && r <= 9 && c >= 1 && c <= 9 && dist[r][c][d] < 0;
}

bool read_input()
{
    string s;
    if (cin >> s && s == "END") return false;
    cout << s << endl;  // name of maze
    cin >> r0 >> c0 >> s >> r2 >> c2;
    d1 = dir(s[0]);
    r1 = r0 + dr[d1];
    c1 = c0 + dc[d1];
    memset(neigh, 0, sizeof(neigh));
    int r, c;
    while(cin >> r && r)
    {
        cin >> c;
        while(cin >> s && s[0] != '*')
        {
            for (int i = 1; i < s.length(); i++)
                neigh[r][c][dir(s[0])][turn(s[i])] = 1;
        }
    }
    return true;
}

void print_output(Node x)
{
    vector<pair<int, int> > path;
    while(dist[x.r][x.c][x.d])
    {
        path.push_back(make_pair(x.r, x.c));
        x = p[x.r][x.c][x.d];
    }
    path.push_back(make_pair(x.r, x.c));
    path.push_back(make_pair(r0, c0));
    int cnt = 0;
    for (int i = path.size()-1; i>=0; i--)
    {
        if (cnt % 10 == 0) cout << " ";
        cout << " (" << path[i].first << "," << path[i].second << ")";
        if (++cnt % 10 == 0) cout << endl;
    }
    if (path.size() % 10) cout << endl;
}

void bfs()
{
    queue<Node> q;
    memset(dist, -1, sizeof(dist));
    Node x(r1, c1, d1), y;
    dist[x.r][x.c][x.d] = 0;
    q.push(x);
    while(!q.empty())
    {
        Node x = q.front(); q.pop();
        if (x.r == r2 && x.c == c2)
        {
            print_output(x);
            return;
        }
        for (int i = 0; i < 3; i++)
            if (neigh[x.r][x.c][x.d][i] && valid(y = walk(x, i)))
            {
                dist[y.r][y.c][y.d] = dist[x.r][x.c][x.d] + 1;
                p[y.r][y.c][y.d] = x;
                q.push(y);
            }
    }
    cout << "  No Solution Possible" << endl;
}

int main()
{
    while(read_input())
        bfs();
    return 0;
}
