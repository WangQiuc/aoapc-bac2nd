// UVa 1662 Brackets Removal
// wangqc
#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>

using namespace std;

const int maxn = 1005;
const char *ops = "*/+-";
char expr[maxn];
int vis[maxn];  // 0 unvisited, 1 visited can be removed; -1 visited cannot be removed

struct Node
{
    int l, r, sz;
    bool operator < (const Node &rhs) const { return sz < rhs.sz || (sz == rhs.sz && l < rhs.l); }
} tree[maxn];

inline int get_op(int x) 
{ 
    const char *pch = strchr(ops, expr[x]);
    return pch == NULL ? 4 : pch - ops;
}

void solve()
{
    memset(vis, 0, sizeof(vis));
    stack<int> s;
    int cnt = 0;
    int n = strlen(expr + 1);
    for(int i = 1; i <= n; i++)
    {
        if(expr[i] == '(') s.push(i);
        else if(expr[i] == ')')
        {
            tree[cnt].l = s.top(); s.pop();
            tree[cnt].r = i;
            tree[cnt].sz = tree[cnt].r - tree[cnt].l;
            cnt++;
        }
    }
    sort(tree, tree+cnt);
    for(int i = 0; i < cnt; i++)
    {
        bool ok = true;
        int L = tree[i].l, R = tree[i].r;
        int lop = get_op(L-1), rop = get_op(R+1);
        if(lop < 2 || rop < 2)
        {
            for(int j = L+1; ok && j < R; j++)
            {
                if(vis[j] == -1) continue;
                if(expr[j] == '+' || expr[j] == '-') ok = false;
            }
            if(!ok) for(int j = L; j <= R; j++)
                if(!vis[j]) vis[j] = -1;
        }
        if(!ok) continue;   // cannot remove
        vis[L] = vis[R] = 1;
        if(lop & 1) for(int j = L+1; ok && j < R; j++) // - or /: need to reverse op after bracket
        {
            if(vis[j] == -1) continue;
            int op = get_op(j);
            if(op >> 1 == lop >> 1) expr[j] = ops[op^1]; // reverse +/- or *//
        }
    }
    for(int i = 1; i <= n; i++) 
        if(vis[i] != 1) cout << expr[i];
    cout << endl;
}

int main()
{
    while(cin >> expr+1)
        solve();
    return 0;
}
