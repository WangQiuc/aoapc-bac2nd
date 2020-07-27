// UVa 658 It's not a Bug, it's a Feature!
// wangqc
#include<iostream>
#include<queue>

using namespace std;
const int maxn = 20, maxm = 105, inf = 0x3fffffff;

struct Node
{
    int s, d;
    Node(int s=0, int d=0): s(s), d(d) {}
    bool operator < (const Node &rhs) const { return d > rhs.d; }
};

int n, m, w[maxm], d[1<<maxn];
bool vis[1<<maxn];
char s[maxm][maxn+5], t[maxm][maxn+5];  // before patch, after patch

int solve()
{
    for(int i = 0; i < (1<<n); i++)
        d[i] = inf, vis[i] = false;
    d[(1<<n)-1] = 0;
    priority_queue<Node> pq;
    pq.push(Node((1<<n)-1, 0));
    while(!pq.empty())
    {
        Node x = pq.top(); pq.pop();
        if(!x.s) return x.d;
        if(vis[x.s]) continue;
        vis[x.s] = true;
        for(int i = 0; i < m; i++)  // linear search m as m <<< (1<<n)
        {
            bool ok = true;
            for(int j = 0; ok && j < n; j++)
            {
                if(s[i][j] == '-' && (x.s >> j & 1)) ok = false;
                if(s[i][j] == '+' && !(x.s >> j & 1)) ok = false;
            }
            if(!ok) continue;
            Node y = Node(x.s, x.d + w[i]);
            for(int j = 0; j < n; j++)  // patch ith patcher
            {
                if(t[i][j] == '+') y.s |= (1<<j);
                if(t[i][j] == '-') y.s &= ~(1<<j);
            }
            if(y.d < d[y.s]) d[y.s] = y.d, pq.push(y);
        }
    }
    return -1;
}

int main()
{
    int kase = 0;
    while(cin >> n >> m && n)
    {
        for(int i = 0; i < m; i++)
            cin >> w[i] >> s[i] >> t[i];
        int ans = solve();
        cout << "Product " << ++kase << endl;
        if(ans < 0) cout << "Bugs cannot be fixed.\n\n";
        else cout << "Fastest sequence takes " << ans << " seconds.\n\n";
    }
    return 0;
}
