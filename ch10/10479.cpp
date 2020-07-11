// UVa 10479 The Hendrie Sequence
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef unsigned long long ull;
const int maxn = 64;
// H(n) = Σh(i), h(i) = Σh(i-1-k)*k+0*(i-1)+i
// H(16) = h(0)+h(1)+h(2)+h(3)+h(4) = 0 1 02 1003 02110004
int dfs(ull n, int i)
{
    ull lh;
    for(int k = 1; k <= i-1; k++)
    {
        int j = i-1-k;
        lh = j ? 1ll<<(j-1) : 1;     // length of h(i), when k=i-1, seg is a single 0
        for(int t = 0; t < k; t++)   // repeat k times
        {
            if(lh < n) n -= lh;
            else return dfs(n, j);
        }
    }
    return i;
}

ull solve(ull n)
{
    if(n-- == 1) return 0;
    for(int i = 0;;i++)
    {
        ull lh = 1ll << i;
        if(lh < n) n -= lh;
        else return dfs(n, i+1);
    }
}

int main()
{
    ull n;
    while(cin >> n && n)
        cout << solve(n) << endl;
    return 0;
}
