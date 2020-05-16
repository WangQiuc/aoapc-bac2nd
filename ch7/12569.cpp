// UVa 12569 Planning mobile robot on Tree
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 15;
struct Node
{   // pid - parent node id, obs - binary representation of obstacles' idx
    int pid, robot, obs, k, src, dst;  
    Node(int p=0, int r=0, int o=0, int k=0, int s=0, int d=0): 
        pid(p), robot(r), obs(o), k(k), src(s), dst(d) {} 
};
Node q[maxn*(1<<maxn)];
vector<int> graph[maxn];
int n, t, vis[maxn][1<<maxn];

void bfs()
{   // i - queue front idx, j - queue rear idx
    for (int i = 0, j = 1; i < j; i++)
    {
        Node u = q[i];
        if (u.robot == t)
        {
            cout << u.k << endl;
            int sz = u.k << 1, p = sz - 1, path[sz];
            while(p >= 0)
                path[p--] = u.dst + 1, path[p--] = u.src + 1, u = q[u.pid];
            for (p = 0; p < sz; p += 2)
                cout << path[p] << " " << path[p+1] << endl;
            cout << endl;
            return;
        }
        for (int x = 0; x < n; x++) if (u.robot == x || (u.obs >> x & 1))
            for (int y : graph[x])  if (u.robot != y && !(u.obs >> y & 1))
            {
                Node v(i, u.robot, u.obs, u.k+1, x, y);
                if (u.robot == x) v.robot = y;  // robot move from x to y
                else v.obs += (1<<y) - (1<<x);  // obstacle move from x to y
                if (!vis[v.robot][v.obs])
                    vis[v.robot][v.obs] = true, q[j++] = v;
            }
    }
    cout << "-1" << endl << endl;
    return;
}

int main()
{
    int m, s, x, y, T, kase = 0;
    cin >> T;
    while (T--)
    {
        cin >> n >> m >> s >> t;
        memset(q, 0, sizeof(q));
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++) graph[i].clear();
        y = 0;
        while (m--)
        {
            cin >> x;
            y |= (1 << (x-1));
        }
        s--, t--;
        vis[s][y] = true;
        Node start(-1, s, y, 0, -1, -1);
        q[0] = start;
        for (int i = 0; i < n-1; i++)
        {
            cin >> x >> y;
            graph[--x].push_back(--y);
            graph[y].push_back(x);
        }
        cout << "Case " << ++kase << ": ";
        bfs();
    }
    return 0;
}
