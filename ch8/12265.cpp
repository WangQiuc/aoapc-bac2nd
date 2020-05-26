// UVa 12265 Selling Land
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1005;
int height[maxn], ans[maxn*2];
char s[maxn][maxn];
// height and top-left corner's col index x
struct Node {
    int x, h;
    Node(int x=0, int h=0): x(x), h(h) {}
} node[maxn];

int main()
{
    int n, m, T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> s[i];
        memset(height, 0, sizeof(height));
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < n; i++)
        {
            int top = -1;
            for (int j = 0; j < m; j++)
            {
                if (s[i][j] != '#') 
                {
                    height[j]++;
                    Node u(j, height[j]);
                    while (top >= 0 && u.h <= node[top].h)
                        u.x = node[top--].x;
                    if (top < 0 || u.h-u.x > node[top].h-node[top].x)  // -x is actually j-x
                        node[++top] = u;    // no need to push a smaller node into stack
                    ans[node[top].h + j-node[top].x+1]++;
                }
                else height[j] = 0, top = -1;
            }
        }
        for (int i = 1; i <= n + m; i++)
            if (ans[i]) cout << ans[i] << " x " << (i<<1) << endl;
    }
    return 0;
}
