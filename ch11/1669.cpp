// UVa 1669 Holiday's Accommodatio
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;
typedef long long ll;

const int maxn = 100005;
vector<pair<int, int> > G[maxn];

int n, cnt[maxn];
ll ans;

// maximize visiting times for all edges
// for edge p->x, max_time = min(dfs_cnt(x), n-dfs_cnt(x))
void dfs(int x, int p)
{
    int y;
    cnt[x] = 1;
    for(auto yw : G[x]) if((y=yw.first) != p)
    {
        dfs(y, x);
        cnt[x] += cnt[y];
        ans += min(cnt[y], n-cnt[y])*yw.second;
    }
}

int main()
{
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> n;
        ans = 0;
        for(int i = 1; i <= n; i++) 
            G[i].clear();
        int x, y, w;
        for(int i = 1; i < n; i++)
        {
            cin >> x >> y >> w;
            G[x].push_back(make_pair(y, w));
            G[y].push_back(make_pair(x, w));
        }
        dfs(1, 0);
        printf("Case #%d: %lld\n", kase, ans<<1);   // both direction, ans * 2
    }
    return 0;
}
