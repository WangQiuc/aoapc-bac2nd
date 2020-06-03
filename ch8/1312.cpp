// UVa 1312 Cricket Field
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 105;
int ys[maxn];
struct Node
{
    int x, y;
    bool operator < (const Node &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
} nodes[maxn];

int main()
{
    int n, W, H, T, kase = 0;
    cin >> T;
    while (T--)
    {
        cin >> n >> W >> H;
        for (int i = 0; i < n; i++)
        {
            cin >> nodes[i].x >> nodes[i].y;
            ys[i] = nodes[i].y;
        }
        ys[n] = 0; ys[n+1] = H;
        sort(nodes, nodes+n);
        sort(ys, ys+n+2);
        int m = unique(ys, ys+n+2) - ys, maxs = 0, maxx, maxy;
        for (int i = 0; i < m; i++)
            for (int j = i+1; j < m; j++)
            {
                int top = ys[i], bottom = ys[j], w = 0, h = bottom - top, px = 0;
                for (int k = 0; k < n; k++) if (top < nodes[k].y && nodes[k].y < bottom)
                {
                    w = nodes[k].x - px;
                    if (min(w, h) > maxs) maxs = min(w, h), maxx = px, maxy = top;
                    px = nodes[k].x;
                }
                if (min(W-px, h) > maxs) maxs = min(W-px, h), maxx = px, maxy = top;
            }
        if (kase++) cout << endl;
        cout << maxx << " " << maxy << " " << maxs << endl;
    }
    return 0;
}
