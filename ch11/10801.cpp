// UVa 10801 Lift Hopping
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

const int maxn = 7, maxf = 100, maxm = 700, wait = 60, inf = 0x3f3f3f3f;

struct Node
{
    int i, d;
    Node(int i=0, int d=0): i(i), d(d) {}
    bool operator < (const Node &rhs) const { return d > rhs.d; }
};
// node id for elevator i's jth stop: (100i+j); f[i], node i's floor
int n, k, t[maxn], d[maxm], f[maxm];
bool vis[maxm]; 
// V: vertical node graph (same elevator's each stop), H: horizontal node graph (same floor's each stopped elevator)
vector<int> V[maxm], H[maxf];  

inline int get_d(int x, int y) { return abs(f[x]-f[y]) * t[x/maxf]; }

inline bool reach_target(int x)
{
    for(int i : H[k])
        if(x == i) return true;
    return false;
}

int dijkstra()
{
    priority_queue<Node> pq;
    memset(d, inf, sizeof(d));
    memset(vis, 0, sizeof(vis));
    for(int x : H[0]) 
        pq.push(Node(x, 0)), d[x] = 0;   // nodes on 0th floor
    while(!pq.empty())
    {
        int a, x = pq.top().i; pq.pop();
        if(reach_target(x)) return d[x];
        if(vis[x]) continue;
        vis[x] = true;
        for(int y : V[x]) if(!vis[y] && (a=d[x]+get_d(x,y)) < d[y])
            pq.push(Node(y, d[y]=a));
        for(int y : H[f[x]]) if(!vis[y] && (a=d[x]+wait) < d[y])
            pq.push(Node(y, d[y]=a));
    }
    return inf;
}

// each evelator's each stop is a node, find the shortest path
// make edge between each stop of the same evelator in V (w=ti), and each evelator on the same floor in H (w=60s)
int main()
{
    while(cin >> n >> k)
    {
        for(int i = 0; i < n; i++)
            cin >> t[i];
        for(int i = 0; i < maxm; i++)
            V[i].clear(), H[i].clear();
        for(int i = 0; i < n; i++)
            for(int j = 0; ;j++)
            {
                int x = i*maxf+j;
                cin >> f[x];
                H[f[x]].push_back(x);
                if(x % maxf) 
                    V[x].push_back(x-1), V[x-1].push_back(x);
                if(getchar() != ' ') break;
            }
        int ans = dijkstra();
        if(ans == inf) cout << "IMPOSSIBLE" << endl;
        else cout << ans << endl;
    }
    return 0;
}
