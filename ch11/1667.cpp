// UVa 1667 Network Mess
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 2005, maxl = 55;
int n, dist[maxn][maxn], a[maxl][maxl], deg[maxn], id[maxl];

int main()
{
    int n;
    while(cin >> n && n)
    {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                cin >> a[i][j];
        memset(deg, 0, sizeof(deg));
        int cnt = 0;
        id[1] = ++cnt;
        dist[1][1] = 0;
        for(int y = 2; y <= n; y++)
        {
            int d, i, j;
            for(int k = 1; k <= cnt; k++)
            {
                d = a[1][y] - dist[1][k];
                bool ok = true;
                for(int x = 2; ok && x < y; x++) 
                    if(a[x][y] - dist[id[x]][k] != d) ok = false;
                if(ok) { i = k; break; }
            }
            for(int k = 1; k <= d; k++)
            {
                deg[i]++, deg[j=++cnt] = 1, dist[j][j] = 0;
                for(int x = 1; x < cnt; x++)
                    dist[j][x] = dist[x][j] = dist[x][i] + 1;
                i = j;
            }
            id[y] = cnt;
        }
        sort(deg+1, deg+cnt+1);
        for(int i = 1; i < cnt; i++)
        {
            if(deg[i] == 1) continue;   // leaf node
            cout << deg[i] << " ";
        }
        cout << deg[cnt] << endl;
    }
    return 0;
}
