// UVa 1322 Minimizing Maximizer
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 50005, inf = 1<<30;
int n, m, tree[maxn*4];

void build(int x, int l, int r)
{
    tree[x] = inf;
    if (l == r) return;
    int m = (l+r)>>1;
    build(x<<1, l, m);
    build(x<<1|1, m+1, r);
}

void update(int i, int x, int v, int l, int r)
{
    tree[x] = min(v, tree[x]);
    if(l == r) return;
    int m = (l+r)>>1;
    if(i <= m) update(i, x<<1, v, l, m);
    else update(i, x<<1|1, v, m+1, r);
}

int query(int x, int i, int j, int l, int r)
{
    if (i <= l && r <= j) return tree[x];
    int m = (l+r)>>1, q1 = inf, q2 = inf;
    if (i <= m) q1 = query(x<<1, i, j, l, m);
    if (j > m) q2 = query(x<<1|1, i, j, m+1, r);
    return min(q1, q2);
}

int main()
{
    int i, j, T;
    cin >> T;
    while(T--)
    {
        cin >> n >> m;
        build(1, 1, n);
        update(1, 1, 0, 1, n);
        while(m--)
        {
            cin >> i >> j;
            int x = query(1, i, j, 1, n);
            update(j, 1, x+1, 1, n);
        }
        cout << query(1, n, n, 1, n) << endl;
        if(T) cout << endl;
    }
    return 0;
}
