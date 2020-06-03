// UVa 1624 Knots
// wangqc
#include<cstdio>

const int maxn = 1000005;
struct Node  {              // linked list node
    int left, right, nei;   // node that overlaps and occludes
} q[maxn];
bool vis[maxn];
int layer[maxn];

void del(int i)
{
    vis[i] = true;
    q[q[i].left].right = q[i].right;
    q[q[i].right].left = q[i].left;
}

// x next to y and x's nei next to y's nei
bool nei_next(int x, int y) { return q[q[x].nei].right == q[y].nei; }

int main()
{
    int n, m, x, y, T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            q[i].left = i-1, q[i].right = i+1, vis[i] = layer[i] = 0;
        q[0].left = n-1, q[n-1].right = 0;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            q[x].nei = y, q[y].nei = x;
            layer[x] = 1, layer[y] = -1;
        }
        for (int i = 0; i < n; i++)
            if (!layer[i]) del(i);
        int p = 0, cnt = 2 * m;
        while (cnt)     // cnt nodes to restore
        {
            bool ok = true;
            while (vis[p]) p++;
            for (int i = q[p].right; ok && i != p; i = q[i].right)
            {
                x = i, y = q[i].right;
                if (layer[x] == layer[y] && (nei_next(x, y) || nei_next(y, x)))
                {   // restore by passing
                    del(x), del(y), del(q[x].nei), del(q[y].nei);
                    cnt -= 4, ok = false;
                }
                else if (q[x].nei == y) 
                {   // restore by self-loop
                    del(x), del(y);
                    cnt -= 2, ok = false;
                }
            }
            if (ok) break;  // some nodes can't be removed (restored)
        }
        printf("Case #%d: %s\n", kase, (cnt ? "NO" : "YES"));
    }
    return 0;
}
