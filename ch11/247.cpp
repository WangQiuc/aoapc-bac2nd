// UVa Calling Cycles
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<vector>

using namespace std;
const int maxn = 30;
int n, m;
bool vis[maxn], d[maxn][maxn];;

vector<string> names;
int ID(const string &s)     // use linear search due to small size
{
    for(int i = 0; i < names.size(); i++)
        if(names[i] == s) return i;
    names.push_back(s);
    return names.size() - 1;
}

void dfs(int x)
{
    vis[x] = true;
    for(int y = 0; y < n; y++) if(!vis[y] && d[x][y] && d[y][x])
    {
        cout << ", " << names[y];
        dfs(y);
    }
}

int main()
{
    string s1, s2;
    int kase = 0;
    while(cin >> n >> m && n)
    {
        names.clear();
        memset(d, 0, sizeof(d));
        for(int i = 0; i < n; i++) d[i][i] = true;
        while(m--)
        {
            cin >> s1 >> s2;
            d[ID(s1)][ID(s2)] = true;
        }
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    d[i][j] |= d[i][k] && d[k][j];
        if(kase) cout << endl;
        cout << "Calling circles for data set " << ++kase << ":\n";
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++) if(!vis[i])
        {
            cout << names[i]; 
            dfs(i);
            cout << endl;
        }
    }
    return 0;
}
