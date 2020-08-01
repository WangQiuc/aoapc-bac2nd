// UVa 1001 Say Cheese
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>

using namespace std;

const int maxn = 105, inf = 1e9;
const double speed = 10;
int n;
double d[maxn];
bool vis[maxn];

struct Point { int x, y, z, r; } p[maxn];

struct Node
{
    int i;
    double d;
    Node(int i=0, double d=0): i(i), d(d) {}
    bool operator < (const Node &rhs) const { return d > rhs.d; }
};

double get_d(int i, int j)
{
    double d = sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y)+(p[i].z-p[j].z)*(p[i].z-p[j].z));
    return d > p[i].r+p[j].r ? d-p[i].r-p[j].r : 0;
}

double dijkstra()
{
    double t;
    for(int i = 0; i < n; i++) d[i] = inf; d[n] = 0, d[n+1] = inf;
    memset(vis, 0, sizeof(vis));
    priority_queue<Node> pq;
    pq.push(Node(n, 0));
    while(!pq.empty())
    {
        int x = pq.top().i; pq.pop();
        if(x == n+1) break;
        if(vis[x]) continue;
        vis[x] = true;
        for(int y = 0; y <= n+1; y++) 
            if(!vis[y] && (t=d[x]+get_d(x,y)) < d[y])
                pq.push(Node(y, (d[y]=t)));
    }
    return d[n+1];
}

int main()
{
    int kase = 0;
    while(cin >> n && n != -1)
    {
        for(int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y >> p[i].z >> p[i].r;
        cin >> p[n].x >> p[n].y >> p[n].z;          // n: src
        cin >> p[n+1].x >> p[n+1].y >> p[n+1].z;    // n+1: dst
        p[n].r = p[n+1].r = 0;
        printf("Cheese %d: Travel time = %.lf sec\n", ++kase, dijkstra()*speed);
    }
    return 0;
}
