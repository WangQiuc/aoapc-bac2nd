// UVa12166 Equilibrium Mobile
// wangqc
#include<iostream>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

typedef long long LL;

int cnt;
string s;
map<LL, int> ctr;

void dfs(int l, int r, int d)
{
    if (s[l] == '[')
    {
        int bal = 0;
        for (int i = l+1; i < r; i++)
        {
            if (s[i] == '[') bal++;
            if (s[i] == ']') bal--;
            if (!bal && s[i] == ',')   // [[<expr>,<expr>],<expr>]
            {                          // l               i      r
                dfs(l+1, i-1, d+1);
                dfs(i+1, r-1, d+1);
            }
        }
    }
    else    // leaf node x, if x's not modified, total weight = wx << dx;
    {
        LL w = 0;   // x's weight
        for (int i = l; i <= r; i++)
            w = w * 10 + s[i] - '0';
        cnt++;
        ctr[w<<d]++;
    }
}

int main()
{
    int T, maxn;
    cin >> T;
    while (T--)
    {
        cin >> s;
        ctr.clear();
        cnt = maxn = 0;
        dfs(0, s.length()-1, 0);
        for (auto kv : ctr)
            maxn = max(maxn, kv.second);
        cout << cnt - maxn << endl;
    }
    return 0;
}
