// UVa 307 Sticks
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
const int maxn = 105;
int n, m, a[maxn], target;
bool vis[maxn];

bool dfs(int len, int i, int cnt)     
{   // current stick length k, add ith stick, matched cnt sticks
    if (cnt == m) return true;
    if (len == target) return dfs(0, 0, cnt+1);
    for (; i < n; i++)  // no need to place a[i] into current stick if a[i-1] has the same length and couldn't be placed either
        if (!vis[i] && (!i || a[i] != a[i-1] || vis[i-1]) && len + a[i] <= target)
        {
            vis[i] = true;
            if (dfs(len+a[i], i+1, cnt)) return true;
            vis[i] = false;
            if (!len || len + a[i] == target) return false;  // a[i] can't be compatible or replaced with other sticks
        }
    return false;
}

int main()
{
    while (cin >> n && n)
    {
        int sum = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++)
            cin >> a[i], sum += a[i];
        sort(a, a+n, greater<int>());
        for(target = a[0]; target <= sum >> 1; target++) if (!(sum % target))
        {   // all origin sticks have same lengths - target
            m = sum / target;
            if (dfs(0, 0, 0)) break;
        }
        cout << (target <= sum >> 1 ? target : sum) << endl;
    }
    return 0;
}
