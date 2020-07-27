// UVa 10048 Audiophobia
// wangqc
#include<iostream>
#include<vector>

using namespace std;
const int maxn = 105, inf = 200000;
int d[maxn][maxn];
int main()
{
    int n, m, q, x, y, w, kase = 0;
    while(cin >> n >> m >> q && n)
    {
        for(int i = 0; i < n; i++)
        {
            d[i][i] = 0;
            for(int j = i+1; j < n; j++)
                d[i][j] = d[j][i] = inf;
        }
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> w; x--, y--;
            d[x][y] = min(d[x][y], w);
            d[y][x] = d[x][y];
        }
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++) if(d[i][k] < inf && d[k][j] < inf)
                    d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));
        if(kase) cout << endl;
        cout << "Case #" << ++kase << endl;
        while(q--)
        {
            cin >> x >> y; x--, y--;
            if(d[x][y] == inf) cout << "no path\n";
            else cout << d[x][y] << endl;
        }
    }
    return 0;
}
