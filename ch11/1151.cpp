// UVa 1151 Buy or Build
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 1005, maxq = 8;
int n, P[maxn], x[maxn], y[maxn], cost[maxq];
vector<int> sub[maxq];
int find(int x) { return x == P[x] ? x : (P[x] = find(P[x])); }

struct Edge
{
    int x, y, w;
    Edge(int x, int y, int w):x(x), y(y), w(w) {}
    bool operator < (const Edge &rhs) const { return w < rhs.w; };
};
vector<Edge> e;

int mst(int cnt, const vector<Edge> &e_in, vector<Edge> *e_out)
{
    if(cnt == 1) return 0;
    int m = e_in.size();
    int ans = 0;
    for(int i = 0; i < m; i++)
    {
        int x = find(e_in[i].x), y = find(e_in[i].y);
        if(x == y) continue;
        P[y] = x;
        ans += e_in[i].w;
        if(e_out) (*e_out).push_back(e_in[i]);
        if(--cnt == 1) break;
    }
    return ans;
}

int main()
{
    int T, q;
    cin >> T;
    while(T--)
    {
        cin >> n >> q;
        for(int i = 0; i < q; i++)
        {
            int cnt; 
            cin >> cnt >> cost[i];
            sub[i].clear();
            while(cnt--)
            {
                int x; 
                cin >> x;
                sub[i].push_back(x-1);
            }
        }
        for(int i = 0; i < n; i++)
            cin >> x[i] >> y[i];
        vector<Edge> e, tree, dummy;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                e.push_back(Edge(i, j, (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])));
        for(int i = 0; i < n; i++) P[i] = i;
        sort(e.begin(), e.end());
        int ans = mst(n, e, &tree);
        for(int s = 0; s < (1<<q); s++)
        {
            for(int i = 0; i < n; i++) P[i] = i;
            int cnt = n, w = 0;
            for(int i = 0; i < q; i++) if (s>>i & 1)
            {
                w += cost[i];
                int p = find(sub[i][0]);
                for(int x : sub[i])
                {
                    int px = find(x);
                    if (px != p) P[px] = p, cnt--;
                }
            }
            ans = min(ans, w + mst(cnt, tree, nullptr));
        }
        cout << ans << endl;
        if(T) cout << endl;
    }
    return 0;
}
