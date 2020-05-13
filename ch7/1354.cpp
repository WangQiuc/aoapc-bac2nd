// UVa 1354 Mobile Computing
// wangqc
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

struct Node
{
    double L, R;
    Node(): L(0), R(0) {}
};
const int maxn = 6;
int n;
bool vis[1 << maxn];
double r, w[maxn], sum[1 << maxn];
vector<Node> tree[1 << maxn];

void dfs(int subset)
{
    if (vis[subset]) return;
    vis[subset] = true;
    bool leaf = true;
    for (int lsub = (subset-1)&subset; lsub; lsub = (lsub-1)&subset)
    {
        leaf = false;
        int rsub = subset ^ lsub;
        double d1 = sum[rsub] / sum[subset];
        double d2 = sum[lsub] / sum[subset];
        dfs(lsub);
        dfs(rsub);
        for (auto lb : tree[lsub])
            for (auto rb : tree[rsub])
            {
                Node x;
                x.L = max(lb.L + d1, rb.L - d2);
                x.R = max(lb.R - d1, rb.R + d2);
                if ((x.L + x.R) < r) tree[subset].push_back(x);
            }
    }
    if (leaf) tree[subset].push_back(Node());
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lf%d", &r, &n);
        for (int i = 0; i < n; i++) 
            scanf("%lf", &w[i]);
        for (int i = 0; i < (1<<n); i++)
        {
            sum[i] = 0;
            tree[i].clear();
            for (int j = 0; j < n; j++)
                if (i & (1<<j)) sum[i] += w[j];
        }
        int root = (1<<n) - 1;
        memset(vis, 0 , sizeof(vis));
        dfs(root);
        double maxr = -1;
        for (auto x : tree[root])
            maxr = max(maxr, x.L + x.R);
        maxr < 0 ? printf("-1\n") : printf("%.10lf\n", maxr);
    }
    return 0;
}
