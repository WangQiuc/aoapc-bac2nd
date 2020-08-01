// UVa 1663 Purifying Machine
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 2050;  // 1<<10

int n, m, N;
char s[15];
int match[maxn];
vector<int> G[maxn];
bool set[maxn], vis[maxn];

// could find an augmenting path or not
int dfs(int i)
{
    for(int j : G[i]) if(!vis[j])
    {
        vis[j] = true;
        if(match[j] == -1 || dfs(match[j]))
        {
            match[i] = j, match[j] = i;  // update the matching to augment match pair
            return 1;
        }
    }
    return 0;
}

int hungarian()
{
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < N; i++) if(match[i] == -1)
    {
        memset(vis, 0, sizeof(vis));
        cnt += dfs(i);
    }
    return cnt;
}

int main()
{
    while(cin >> n >> m && n)
    {
        N = 1<<n;
        for(int i = 0; i < N; i++) set[i] = false, G[i].clear();
        for(int i = 0; i < m; i++)
        {
            cin >> s;
            int x = 0, p = -1;
            for(int j = 0; j < n; j++)
            {
                if(s[j]=='1') x |= 1<<j;
                else if(s[j] == '*') p = j;
            }
            set[x] = true;
            if(p != -1) set[x | 1<<p] = true;
        }
        int m = 0;
        for(int i = 0; i < N; i++) if(set[i])
        {
            m++;
            for(int j = 0; j < n; j++) if(set[i ^ 1<<j])
                G[i].push_back(i ^ 1<<j);  // only have one bit diff, can be matched
        }
        cout << m-hungarian() << endl;
    }
    return 0;
}
