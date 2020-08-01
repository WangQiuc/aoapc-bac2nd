// UVa 821 Page Hopping
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;
const int maxn = 100;

vector<int> nodes;
int d[maxn][maxn];
bool vis[maxn];

int main()
{
    int x, y, kase = 0;
    while(cin >> x >> y && x)
    {
        memset(vis, 0, sizeof(vis));
        memset(d, maxn, sizeof(d));
        nodes.clear();
        do 
        {
            d[--x][--y] = 1, d[x][x] = 0;
            if(!vis[x]) nodes.push_back(x), vis[x] = true;
        }
        while(cin >> x >> y && x);
        for(int k : nodes)
            for(int i : nodes)
                for(int j : nodes) if(d[i][k] < maxn && d[k][j] < maxn)
                    d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
        double s = 0;
        for(int i : nodes)
            for(int j : nodes) if(i != j)
                s += d[i][j];
        printf("Case %d: average length between pages = %.3lf clicks\n", ++kase, s / (nodes.size()*(nodes.size()-1)));
    }
    return 0;
}
