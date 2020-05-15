// UVa 10603 Fill
// wangqc
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

struct Node
{
    int v[3], d;
    bool operator < (const Node &rhs) const { return d > rhs.d; }
};
const int maxn = 205;
bool vis[maxn][maxn];
int cap[3], dist[maxn];

void solve(int a, int b, int c, int d)
{
    cap[0] = a, cap[1] = b, cap[2] = c;
    memset(vis, 0, sizeof(vis));
    memset(dist, -1, sizeof(dist));
    priority_queue<Node> pq;
    Node x;
    x.v[0] = 0, x.v[1] = 0, x.v[2] = c, x.d = 0;
    pq.push(x);
    vis[0][0] = true;
    while (!pq.empty())
    {
        Node x = pq.top(); pq.pop();
        for (int t : x.v)
            if (dist[t] < 0) dist[t] = x.d;
        if (dist[d] >= 0) break;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i != j && x.v[i] && x.v[j] != cap[j])
                {
                    int w = min(x.v[i], cap[j]-x.v[j]);
                    Node y;
                    memcpy(&y, &x, sizeof(y));
                    y.d = x.d + w;
                    y.v[i] -= w;
                    y.v[j] += w;
                    if (!vis[y.v[0]][y.v[1]])
                    {
                        vis[y.v[0]][y.v[1]] = true;
                        pq.push(y);
                    }
                }
    }
    while (d >= 0)
    {
        if (dist[d] >= 0)
        {
            printf("%d %d\n", dist[d], d);
            return;
        }
        d--;
    }
}

int main()
{
    int T, a, b, c, d;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0;
}
