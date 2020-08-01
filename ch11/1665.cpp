// UVa
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 1000005, maxt = 100005;
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};

struct Node
{
    int i, j, w;
    bool operator < (const Node &rhs) const { return w > rhs.w; }
} nodes[maxn];

int p[maxn], a[maxn], t[maxt], ans[maxt];

int find(int x) { return x == p[x] ? x : p[x]=find(p[x]); }

int main()
{
    int n, m, q, T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m;
        int k = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
            {
                cin >> a[k];
                p[k] = k;
                nodes[k].i = i, nodes[k].j = j, nodes[k].w = a[k];
                k++;
                
            }
        sort(nodes, nodes+k);
        cin >> q;
        for(int i = 0; i < q; i++)
            cin >> t[i];
        k = ans[q] = 0;
        for(int i = q-1; i >= 0; i--)
        {
            ans[i] = ans[i+1];
            while(t[i] < nodes[k].w && k < n*m)
            {
                ans[i]++;
                int u = find(nodes[k].i*m + nodes[k].j);
                for(int d = 0; d < 4; d++)
                {
                    int x = nodes[k].i + dx[d];
                    int y = nodes[k].j + dy[d];
                    if(0 <= x && x < n && 0 <= y && y < m)
                    {
                        int id = x*m + y;
                        if(a[id] <= t[i]) continue;
                        int v = find(id);
                        if(u != v)
                            p[v] = u, ans[i]--;
                    }
                }
                k++;
            }
        }
        for(int i = 0; i < q; i++) cout << ans[i] << " ";
        cout << endl;
        
    }
    return 0;
}
