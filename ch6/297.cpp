// UVa297 Qudatrees
// wangqc

#include <cstdio>
#include <cstring>

const int len = 32;
const int maxn = 1300;  // 1024 * (5 / 4) = 1280
char s[maxn];
int tree[len][len], p, cnt;

void dfs(int x, int y, int w)
{
    char c = s[p++];
    if (c == 'f')
    {
        for (int i = x; i < x+w; i++)
            for (int j = y; j < y+w; j++)
                if (!tree[i][j]) tree[i][j] = 1, cnt++;
    }
    if (c == 'p')
    {
        w >>= 1;
        dfs(x,   y+w, w);
        dfs(x,   y,   w);
        dfs(x+w, y,   w);
        dfs(x+w, y+w, w);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(tree, 0, sizeof(tree));
        cnt = 0;
        for (int i = 0; i < 2; i++)
        {
            scanf("%s", s);
            p = 0;
            dfs(0, 0, len);
        }
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}
