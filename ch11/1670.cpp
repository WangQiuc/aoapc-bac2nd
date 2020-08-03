// UVa 1670 Kingdom Roadmap
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 100005;

int cnt, a[maxn];
vector<int> G[maxn];

void dfs(int x, int p)
{
    for(int y : G[x]) if(y != p)
        dfs(y, x);
    if(G[x].size() == 1)    // mark leaf node
        a[cnt++] = x;
}

// add edges between leaf nodes
int main()
{
    int x, y, n;
    while(cin >> n)
    {
        for(int i = 1; i <= n; i++)
            G[i].clear();
        for(int i = 1; i < n; i++)
        {
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cnt = 0;
        dfs(1, 0);
        cout << ((cnt+1)>>1) << endl;
        int offset = cnt>>1, m = (cnt-1)>>1;
        for(int i = 0; i <= m; i++)
            cout << a[i] << " " << a[i+offset] << endl;
    }
    return 0;
}
