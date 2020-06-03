// UVa 1580 Pirate Chest
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

int a, b, m, n, pond[505][505], depth[505];
long long maxv, V, S;
int main()
{
    while (cin >> a >> b >> m >> n)
    {
        maxv = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> pond[i][j];
        if (b < a) swap(a, b);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                memset(depth, 0x3f, sizeof(depth));
                for (int r = i; r < min(m, i+b); r++)
                {
                    int h = r - i + 1;
                    for (int c = j; c < min(n, j+b); c++)
                    {
                        int w = c - j + 1;
                        if (min(w, h) > a) break;
                        depth[c] = min(depth[c], pond[r][c]);
                        if (c) depth[c] = min(depth[c], depth[c-1]);  // rolling
                        S = 1LL * w * h;
                        V = S * depth[c];
                        maxv = max(maxv, 1LL * ((V-1) / (n*m-S) + depth[c]) * S);
                    }
                }
            }
        cout << maxv << endl;
    }
    return 0;
}
