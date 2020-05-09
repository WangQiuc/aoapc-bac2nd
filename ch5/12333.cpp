// UVa12333 Revenge of Fibonacci
// wangqc

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int maxd = 50;
const int maxn = 100001;
int fid = 0;
struct BigInt
{
    int base[maxd] = {1}, exp = 0;
    void right_shift(int carry)
    {
        for (int i = 0; i < maxd - 1; i++)
            base[i] = base[i+1];
        base[maxd - 1] = carry;
        exp++;
    }
    void operator+=(BigInt &rhs)
    {
        if (exp < rhs.exp) right_shift(0);
        else if (exp > rhs.exp) rhs.right_shift(0);
        int carry = 0;
        for (int i = 0; i < maxd; i++)
        {
            int d = base[i] + rhs.base[i] + carry;
            base[i] = d % 10, carry = d / 10;
        }
        if (carry) right_shift(1);
    }
};
struct Node
{
    int fid;        // use to track origin id after sorting
    string s;
    bool operator <(const Node &rhs) const
    {
        return s < rhs.s;
    }
} fnodes[maxn];

inline void gen_node(const BigInt &x, Node &node)
{
    int i = maxd - 1;
    for (; !x.base[i]; i--);
    for (int j = 0; i >= 0 && j < 40; i--, j++)
    {
        node.s += char(x.base[i] + '0');
    }
    node.fid = fid++;
}

int bisect(int lo, int hi, const string &s)
{
    if (lo + 1 >= hi) return lo;
    int mid = (lo + hi) >> 1;
    return s <= fnodes[mid].s ? bisect(lo, mid, s) : bisect(mid, hi, s);
}

int main()
{
    BigInt f1, f2;
    for (int i = 1; i < maxn; f1 += f2, f2 += f1)
    {
        gen_node(f1, fnodes[i++]);
        gen_node(f2, fnodes[i++]);
    }
    fnodes[0].s = "0";
    sort(fnodes, fnodes + maxn);
    int T, kase = 0;
    string s;
    cin >> T;
    while (T--)
    {
        cin >> s;
        int n = s.size(), i = bisect(0, maxn - 1, s) + 1, ans = -1;
        // could have multiple match, need to find the one with smallest fid
        for (; i < maxn && fnodes[i].s.substr(0, n) == s; i++)
            ans = ans == -1 ? fnodes[i].fid : min(ans, fnodes[i].fid);
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}
