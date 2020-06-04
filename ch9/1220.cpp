// UVa 1220 Party at Hali-Bula
// wangqc
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

const int maxn = 205;
vector<int> graph[maxn];
int id, n, memo[maxn][2];
bool uni[maxn][2];  
map<string, int> idx;

int get_idx(const string &s)
{
    if (!idx.count(s)) idx[s] = id++;
    return idx[s];
}

// dp[x][i] max # at node x, k: 0 not choose x, 1 choose x
int dp(int x, int k)  
{
    memo[x][k] = k, uni[x][k] = true;
    for (int y : graph[x])
    {
        if (k)
            memo[x][1] += dp(y,0), uni[x][1] &= uni[y][0];
        else
        {
            memo[x][0] += max(dp(y,0), dp(y,1));
            if (memo[y][0] == memo[y][1]) uni[x][0] = false;    // y can be both chosen or not chosen so not unique
            else if (memo[y][0] > memo[y][1]) uni[x][0] &= uni[y][0];
            else uni[x][0] &= uni[y][1];
        }
    }
    return memo[x][k];
}

int main()
{
    string s, s2;
    while (cin >> n >> s)
    {
        id = 0;
        idx.clear();
        for (int i = 0; i < n; i++)
            graph[i].clear();
        get_idx(s);
        for (int i = 0; i < n-1; i++)
        {
            cin >> s >> s2;
            graph[get_idx(s2)].push_back(get_idx(s));
        }
        cout << max(dp(0, 0), dp(0, 1)) << " ";
        bool unique = memo[0][0] == memo[0][1] ? false : (memo[0][0] > memo[0][1] ? uni[0][0] : uni[0][1]);
        cout << (unique ? "Yes\n" : "No\n");
    }
    return 0;
}
