// UVa 818 Cutting Chains
// wangqc
#include<iostream>
#include<cstring>
#define BIT(s, b) (s >> b & 1)

using namespace std;

const int maxn = 15;
int n, seq, minc;
bool edge[maxn][maxn], vis[maxn];


bool check_degree()          // all nodes' degree <= 2
{
    for (int x = 0; x < n; x++)
    {
        int cnt = 0;
        for (int y = 0; y < n; y++)
        {
            cnt += edge[x][y] && BIT(seq, x) && BIT(seq, y);
            if (cnt == 3) return false;
        }
    }
    return true;
}

bool dfs(int x, int p)       // true - has cycle
{
    vis[x] = true;
    for (int y = 0; y < n; y++)
        if (edge[x][y] && y != p && BIT(seq, y))
            if (vis[y] || dfs(y, x)) return true;
    return false;
}

int count_cc()      // cc# <= open circles# + 1
{
    int cnt = 0;
    for (int x = 0; x < n; x++)
        if (!vis[x] && BIT(seq, x))
        {
            if (dfs(x, -1)) return 0;
            cnt++;
        }
    return cnt;
}

// exhaustive search all subsets' bit sequence, bit i = 0 if ith circle is open
// if circle i is open, edge[i][?] is invalid
int main()
{
    int x, y, cccnt, kase = 0; // count of connected components
    while(cin >> n && n)
    {  
        memset(edge, 0, sizeof(edge));
        while (cin >> x >> y && x != -1)
            edge[x-1][y-1] = edge[y-1][x-1] = true;
        minc = maxn;
        for (seq = 0; seq < (1<<n); seq++)
        {
            memset(vis, 0, sizeof(vis));
            if (check_degree() && (cccnt = count_cc()))
            {
                int cnt = 0;
                for (int b = 0; b < n; b++)
                    cnt += !BIT(seq, b);
                if (cccnt <= cnt + 1 && minc > cnt) minc = cnt;
            }
        }
        cout << "Set " << ++kase << ": Minimum links to open is " << minc << endl;
    }
    return 0;
}
