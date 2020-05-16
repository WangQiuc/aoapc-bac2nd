// UVa 1533 Moving Pegs
// wangqc
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 15;
const int edge[][6] = 
{
    {-1,-1,-1,-1, 1, 2},
    {-1, 0,-1, 2, 3, 4},
    { 0,-1, 1,-1, 4, 5},
    {-1, 1,-1, 4, 6, 7},
    { 1, 2, 3, 5, 7, 8},
    { 2,-1, 4,-1, 8, 9},
    {-1, 3,-1, 7,10,11},
    { 3, 4, 6, 8,11,12},
    { 4, 5, 7, 9,12,13},
    { 5,-1, 8,-1,13,14},
    {-1, 6,-1,11,-1,-1},
    { 6, 7,10,12,-1,-1},
    { 7, 8,11,13,-1,-1},
    { 8, 9,12,14,-1,-1},
    { 9,-1,13,-1,-1,-1},
};
int target;

struct Node
{
    int state, d, path[N];
    Node(int s, int d): state(s), d(d) {}
};

void bfs()
{
    queue<Node> q;
    bool vis[1<<N] = {0};
    Node u((1<<N)-1 ^ target, 0);
    q.push(u);
    while (!q.empty())
    {
        u = q.front(); q.pop();
        for (int x = 0; x < 15; x++) if (u.state>>x & 1)
            for (int k = 0; k < 6; k++) if (edge[x][k] != -1 && u.state >> edge[x][k] & 1)
            {
                Node v = u;
                int y = x;
                while (y >= 0 && v.state >> y & 1)  // jump over consecutive pegs
                {
                    v.state ^= 1 << y;
                    y = edge[y][k];
                }
                if (y < 0 || vis[v.state |= 1<<y]) continue;
                vis[v.state] = true;
                v.path[v.d++] = ((x+1)<<4) + y+1;
                if (v.state == target)
                {
                    cout << v.d << endl << (v.path[0]>>4) << " " << (v.path[0]&N);
                    for (int i = 1; i < v.d; i++) 
                        cout << " " << (v.path[i]>>4) << " " << (v.path[i]&N);
                    cout << endl;
                    return;
                }
                q.push(v); 
            }
    }
    cout << "IMPOSSIBLE" << endl;
}


int main()
{
    int t, T;
    cin >> T;
    while (T--)
    {
        cin >> t;
        target = 1 << (t-1);     // target state, only one peg at index t-1
        bfs();
    }
    return 0;
}
