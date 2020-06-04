// UVa 12186 Another Crisis
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 100005;
int n, T;
vector<int> graph[maxn];

int dp(int x)   // miminum employee # required from node x
{
    if (graph[x].empty()) return 1; // leaf node
    int k = (graph[x].size()*T - 1) / 100 + 1; // at least k subordinates required
    vector<int> cnt;
    for (int y : graph[x])
        cnt.push_back(dp(y));    
    sort(cnt.begin(), cnt.end());
    int ans = 0;
    for (int i = 0; i < k; i++)
        ans += cnt[i];
    return ans;
}


int main()
{
    int x;
    while (cin >> n >> T && n)
    {
        for (int i = 0; i <= n; i++) 
            graph[i].clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> x;
            graph[x].push_back(i);
        }
        cout << dp(0) << endl;
    }
    return 0;
}
