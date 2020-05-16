// UVa 11846 Finding Seats Again
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 25;
int n, k;
char graph[maxn][maxn], seat[maxn][maxn];

bool dfs(int p, char c)
{   
    while (seat[p/n][p%n] != '.') p++;
    if (p == n*n) return true;
    int x0 = p/n, y0 = p%n, m = n;  // y's right limit in current dfs
    for (int x = x0; x < n; x++)
        for (int y = y0; y < m; y++)
        {
            if (seat[x][y] != '.') { m = y; break; }
            int s = (x-x0+1) * (y-y0+1);        // size of a rectangular
            if (s > 9) { m = y; break; }
            int sz = 30;  // group size, should be only one digit i in the rectangular
            bool ok = true;
            for (int i = x0; ok && i <= x; i++)
                for (int j = y0; j <= y; j++) if (graph[i][j] != '.')
                {
                    if (sz != 30) {ok = false; break;}
                    sz = graph[i][j] - '0';
                }
            if (!ok || sz < s) {m = y; break;}  // stop expanding
            if (sz > s) continue;               // keep expanding
            // got a rectangular whose area == sz, move |y - y0| forward
            for (int i = x0; i <= x; i++) for (int j = y0; j <= y; j++) seat[i][j] = c;
            if (dfs(p + y - y0 + 1, c + 1)) return true;
            for (int i = x0; i <= x; i++) for (int j = y0; j <= y; j++) seat[i][j] = '.';
        }
    return false;
}

int main()
{
    while (cin >> n >> k && n && k)
    {
        memset(seat, '.', sizeof(seat));
        for (int i = 0; i < n; i++) cin >> graph[i];
        dfs(0, 'A');
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cout << seat[i][j];
            cout << endl;
        }
    }
    return 0;
}
